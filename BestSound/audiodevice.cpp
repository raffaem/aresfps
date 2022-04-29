//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audiodevice.hpp"

#pragma comment(lib,"efx-util.lib")

//function for internal use
size_t ov_read_func(void *ptr, size_t size, size_t nmemb, void *datasource){return fread(ptr, size, nmemb, (FILE*)datasource);}
int ov_seek_func(void *datasource, ogg_int64_t offset, int whence){	return fseek((FILE*)datasource, (long)offset, whence);}
int ov_close_func(void *datasource){   return fclose((FILE*)datasource);}
long ov_tell_func(void *datasource){return ftell((FILE*)datasource);}
//end
BestSound::AudioDevice* currently_device;
void KillAudioDevice() {
	delete currently_device;
}
BS_API BestSound::AudioDevice* BestSound::createAudioDevice(int argc,char** argv) {
	BestSound::AudioDevice* a=new BestSound::AudioDevice(argc,argv);
	atexit(KillAudioDevice);
	return a;
}

//----------------------------------------------------------------
BestSound::AudioDevice::~AudioDevice() {
	alutExit();
}
BestSound::AudioDevice::AudioDevice(int argc,char** argv){
	alutInit(&argc,argv);
	IniEFXExtention();
}

bool BestSound::AudioDevice::OpenSound(std::string filename,BestSound::Sound& sound,BestSound::Source& source) {
	ALuint buffer;
	//get file format
	std::string extention=filename;
	int pos=filename.find_last_of('.');
	if(pos<0) return false;
	extention.erase(0,pos+1);
	//end
	if(extention!="wav"&&
		extention!="raw"&&
		extention!="au"&&
		extention!="ogg") return false;

	//ceck if the source is already created,if not create it
	if(source.source==0) {
		if(!this->CreateSource(source))
			return false;
	}
	//end of cecktion

	//OGG SPECIFIC
	//variables
	if(extention=="ogg") {
		std::vector<char> vector_buffer;
		ALenum format;
		ALsizei freq;

		if(!this->OggFileToPCM((char*)filename.c_str(),vector_buffer,format,freq))
			return false;

		alGenBuffers(1,&sound.buffer);
		alBufferData(sound.buffer, format, &vector_buffer[0], static_cast < ALsizei > (vector_buffer.size()), freq);
		source.AttachSound(sound);
		return true;
	}
	//END OF OGG SPECIFIC

	buffer=alutCreateBufferFromFile(filename.c_str());
	if(alutGetError()!=ALUT_ERROR_NO_ERROR)
		return false;

	sound.buffer=buffer;

	bool err=source.AttachSound(sound);
	if(err==false)
		return false;

	return true;
}

bool BestSound::AudioDevice::OpenSoundOggStream(
	std::string filename,
	BestSound::SoundOggStream& sound,
	BestSound::SourceOggStream& source) {

	//get file format
	std::string extention=filename;
	int pos=filename.find_last_of('.');
	if(pos<0) return false;
	extention.erase(0,pos+1);
	//end

	if(extention!="ogg") return false;

	//buffer=alutCreateBufferFromFile(filename.c_str());
	source.AttachSoundOggStream(sound);
	source.open(filename.c_str());

	this->ogg_streams.push_back(&source);

	return true;
}

bool BestSound::AudioDevice::OpenSoundOggStream(
	BestSound::SoundOggStream& already_open_sound,
	BestSound::SourceOggStream& source,
	BestSound::SoundOggStream& new_sound) {

	//ceck if the sound is already open
	if(already_open_sound.vorbisInfo==NULL)
		return false;

	//buffer=alutCreateBufferFromFile(filename.c_str());
	source.AttachSoundOggStream(new_sound);
	source.open(already_open_sound.filename_path);
	this->ogg_streams.push_back(&source);
	return true;
}

bool BestSound::AudioDevice::CreateSource(BestSound::Source& source) {
	ALuint al_source;
	alGenSources(1, &al_source);

	if (alGetError()!=ALUT_ERROR_NO_ERROR)
		return false;
    
	source.source=al_source;
	return true;
}

void BestSound::AudioDevice::EraseOggStream(int i) {
	/*
	if(this->ogg_streams[i]->loop) {
		this->ogg_streams[i]->release();
		this->ogg_streams[i]->loop=true;
		this->ogg_streams[i]->playback();
		return;
	}

	else {
		this->ogg_streams[i]->release();
		this->ogg_streams.erase(this->ogg_streams.begin()+i);
	}
	*/
}

void BestSound::AudioDevice::Update() {
	for(int i=0;i<this->ogg_streams.size();i++) {

		if(this->ogg_streams[i]->active) {

		if(!this->ogg_streams[i]->loop) {
			bool value=ogg_streams[i]->update();
			if(value==false)
				 this->ogg_streams.erase(this->ogg_streams.begin()+i);

			if(!this->ogg_streams[i]->playing()) {
				if(!this->ogg_streams[i]->playback()) {
					throw std::string("Ogg abruptly stopped.");
					this->ogg_streams.erase(this->ogg_streams.begin()+i);
				}
				else
			  this->ogg_streams.erase(this->ogg_streams.begin()+i);
			}
		}
	//}//if(!this->ogg_streams[i]->loop) {

		if(this->ogg_streams[i]->loop) {
			if(!this->ogg_streams[i]->update())	{
				if(this->ogg_streams[i]->seek(0))
					this->ogg_streams[i]->playback();
				else
					throw "Cannot seek file.";
			}//if
		}// if(this->ogg_streams[i]->loop) {

		}//if(this->ogg_streams[i]->active) {

	}//for
}//function

bool BestSound::AudioDevice::OggFileToPCM(
				  char *fileName,
				  std::vector < char > &buffer,
				  ALenum &format,
				  ALsizei &freq)
{
  int endian = 0;             // 0 for Little-Endian, 1 for Big-Endian
  int bitStream;
  long bytes;
  char array[OGG_NOT_STREAM_BUFFER_SIZE];  // Local fixed size array
  FILE *f;

  // Open for binary reading
  f = fopen(fileName, "rb");

  if(!f)
	  return false;

  vorbis_info *pInfo;
  OggVorbis_File oggFile;

  	// Open Ogg Stream
	ov_callbacks	sCallbacks;
	sCallbacks.read_func = ov_read_func;
	sCallbacks.seek_func = ov_seek_func;
	sCallbacks.close_func = ov_close_func;
	sCallbacks.tell_func = ov_tell_func;
	// Create an OggVorbis file stream
	int result=ov_open_callbacks(f, &oggFile, NULL, 0, sCallbacks);

	if(result!=0)
		return false;

// Get some information about the OGG file
  pInfo = ov_info(&oggFile, -1);

  // Check the number of channels... always use 16-bit samples
  if (pInfo->channels == 1)
      format = AL_FORMAT_MONO16;
  else if (pInfo->channels == 2)
      format = AL_FORMAT_STEREO16;
  else if (pInfo->channels == 4)
	  format = alGetEnumValue("AL_FORMAT_QUAD16");
  else if (pInfo->channels == 6)
	  format = alGetEnumValue("AL_FORMAT_51CHN16");
  else
	  return false;
  // end check

  // The frequency of the sampling rate
  freq = pInfo->rate;
  do {
    // Read up to a buffer's worth of decoded sound data
    bytes = ov_read(&oggFile, array, OGG_NOT_STREAM_BUFFER_SIZE, endian, 2, 1, &bitStream);

	if(bytes<0)
		return false;

    // Append to end of buffer
    buffer.insert(buffer.end(), array, array + bytes);
  } while (bytes > 0);

  ov_clear(&oggFile);
  return true;
}

bool BestSound::AudioDevice::SetDopplerFactor(float factor) {
	alDopplerFactor(factor);
	if(alGetError()!=AL_NO_ERROR)
		return false;
	return true;
}

bool BestSound::AudioDevice::SetSpeedOfSound(float speed_of_sound) {
	alSpeedOfSound(speed_of_sound);
	if(alGetError()!=AL_NO_ERROR)
		return false;
	return true;
}