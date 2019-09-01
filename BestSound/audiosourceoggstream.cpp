//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audiosourceoggstream.hpp"

void BestSound::SourceOggStream::Play() {
	this->playback();
	this->active=true;
}

void BestSound::SourceOggStream::Stop() {
	Source::Stop();
	this->empty();
	this->active=false;
	this->seek(0);
}

void BestSound::SourceOggStream::Pause() {
	Source::Stop();
	this->empty();
	this->active=false;
}

void BestSound::SourceOggStream::Rewind() {
	if(!this->IsPlaying()) {
		this->seek(0);
		return;
	}
	else{
		this->Stop();
		this->Play();
	}
}

void BestSound::SourceOggStream::SetLoopMode(bool value) {
	this->loop=value;
}

void BestSound::SourceOggStream::AttachSoundOggStream(
						  BestSound::SoundOggStream& sound) {
	this->sound=&sound;
}

/************************************************************************************************************************
	The following function are the vorbis callback functions.  As their names suggest, they are expected to work in exactly the
	same way as normal c io functions (fread, fclose etc.).  Its up to us to return the information that the libs need to parse
	the file from memory
************************************************************************************************************************/
//---------------------------------------------------------------------------------
// Function	: VorbisRead
// Purpose	: Callback for the Vorbis read function
// Info		: 
//---------------------------------------------------------------------------------
size_t VorbisRead(void *ptr			/* ptr to the data that the vorbis files need*/, 
				  size_t byteSize	/* how big a byte is*/, 
				  size_t sizeToRead /* How much we can read*/, 
				  void *datasource	/* this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/)
{
	size_t				spaceToEOF;			// How much more we can read till we hit the EOF marker
	size_t				actualSizeToRead;	// How much data we are actually going to read from memory
	SOggFile*			vorbisData;			// Our vorbis data, for the typecast

	// Get the data in the right format
	vorbisData = (SOggFile*)datasource;

	// Calculate how much we need to read.  This can be sizeToRead*byteSize or less depending on how near the EOF marker we are
	spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
	if ((sizeToRead*byteSize) < spaceToEOF)
		actualSizeToRead = (sizeToRead*byteSize);
	else
		actualSizeToRead = spaceToEOF;	
	
	// A simple copy of the data from memory to the datastruct that the vorbis libs will use
	if (actualSizeToRead)
	{
		// Copy the data from the start of the file PLUS how much we have already read in
		memcpy(ptr, (char*)vorbisData->dataPtr + vorbisData->dataRead, actualSizeToRead);
		// Increase by how much we have read by
		vorbisData->dataRead += (actualSizeToRead);
	}

	// Return how much we read (in the same way fread would)
	return actualSizeToRead;
}

//---------------------------------------------------------------------------------
// Function	: VorbisSeek
// Purpose	: Callback for the Vorbis seek function
// Info		: 
//---------------------------------------------------------------------------------
int VorbisSeek(void *datasource		/*this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/, 
			   ogg_int64_t offset	/*offset from the point we wish to seek to*/, 
			   int whence			/*where we want to seek to*/)
{
	size_t				spaceToEOF;		// How much more we can read till we hit the EOF marker
	ogg_int64_t			actualOffset;	// How much we can actually offset it by
	SOggFile*			vorbisData;		// The data we passed in (for the typecast)

	// Get the data in the right format
	vorbisData = (SOggFile*)datasource;

	// Goto where we wish to seek to
	switch (whence)
	{
	case SEEK_SET: // Seek to the start of the data file
		// Make sure we are not going to the end of the file
		if (vorbisData->dataSize >= offset)
			actualOffset = offset;
		else
			actualOffset = vorbisData->dataSize;
		// Set where we now are
		vorbisData->dataRead = (int)actualOffset;
		break;
	case SEEK_CUR: // Seek from where we are
		// Make sure we dont go past the end
		spaceToEOF = vorbisData->dataSize - vorbisData->dataRead;
		if (offset < spaceToEOF)
			actualOffset = (offset);
		else
			actualOffset = spaceToEOF;	
		// Seek from our currrent location
		vorbisData->dataRead += actualOffset;
		break;
	case SEEK_END: // Seek from the end of the file
		vorbisData->dataRead = vorbisData->dataSize+1;
		break;
	default:
		printf("*** ERROR *** Unknown seek command in VorbisSeek\n");
		break;
	};

	return 0;
}

//---------------------------------------------------------------------------------
// Function	: VorbisClose
// Purpose	: Callback for the Vorbis close function
// Info		: 
//---------------------------------------------------------------------------------
int VorbisClose(void *datasource /*this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/)
{
	// This file is called when we call ov_close.  If we wanted, we could free our memory here, but
	// in this case, we will free the memory in the main body of the program, so dont do anything
	return 1;
}

//---------------------------------------------------------------------------------
// Function	: VorbisTell
// Purpose	: Classback for the Vorbis tell function
// Info		: 
//---------------------------------------------------------------------------------
long VorbisTell(void *datasource /*this is a pointer to the data we passed into ov_open_callbacks (our SOggFile struct*/)
{
	SOggFile*	vorbisData;

	// Get the data in the right format
	vorbisData = (SOggFile*)datasource;

	// We just want to tell the vorbis libs how much we have read so far
	return vorbisData->dataRead;
}
/************************************************************************************************************************
	End of Vorbis callback functions
************************************************************************************************************************/

void BestSound::SourceOggStream::open(std::string path)
{

	/************************************************************************************************************************
		Heres a total bodge, just to get the file into memory.  Normally, the file would have been loaded into memory
		for a specific reason e.g. loading it from a pak file or similar.  I just want to get the file into memory for
		the sake of the tutorial.
	************************************************************************************************************************/

	FILE*   tempOggFile;
	int		sizeOfFile; 
	char	tempChar;
	int		tempArray;

    if(!(tempOggFile = fopen(path.c_str(), "rb")))
        throw std::string("Could not open Ogg file.");

	// Find out how big the file is
	sizeOfFile = 0;
	while (!feof(tempOggFile))
	{
		tempChar = getc(tempOggFile);
		sizeOfFile++;
	}

	// Save the data into memory
	sound->oggMemoryFile.dataPtr = new char[sizeOfFile];
	rewind(tempOggFile);
	tempArray = 0;
	while (!feof(tempOggFile))
	{
		sound->oggMemoryFile.dataPtr[tempArray] = getc(tempOggFile);
		tempArray++;
	}

	// Close the ogg file
	fclose(tempOggFile);

	// Save the data in the ogg memory file because we need this when we are actually reading in the data
	// We havnt read anything yet
	sound->oggMemoryFile.dataRead = 0;
	// Save the size so we know how much we need to read
	sound->oggMemoryFile.dataSize = sizeOfFile;	

	/************************************************************************************************************************ 
		End of nasty 'just stick it in memory' bodge...
	************************************************************************************************************************/



	// This is really the only thing that is different from the original lesson 8 file...

	// Now we have our file in memory (how ever it got there!), we need to let the vorbis libs know how to read it
	// To do this, we provide callback functions that enable us to do the reading.  the Vorbis libs just want the result
	// of the read.  They dont actually do it themselves
	// Save the function pointersof our read files...
	sound->vorbisCallbacks.read_func = VorbisRead;
	sound->vorbisCallbacks.close_func = VorbisClose;
	sound->vorbisCallbacks.seek_func = VorbisSeek;
	sound->vorbisCallbacks.tell_func = VorbisTell;

	// Open the file from memory.  We need to pass it a pointer to our data (in this case our SOggFile structure),
	// a pointer to our ogg stream (which the vorbis libs will fill up for us), and our callbacks
	if (ov_open_callbacks(
		&sound->oggMemoryFile,
		&sound->oggStream,
		NULL,
		0,
		sound->vorbisCallbacks) != 0)

		throw std::string("Could not read Ogg file from memory");



	/************************************************************************************************************************
		From now on, the code is exactly the same as in Jesse Maurais's lesson 8
	************************************************************************************************************************/
    
    sound->vorbisInfo = ov_info(&sound->oggStream, -1);
    sound->vorbisComment = ov_comment(&sound->oggStream, -1);

	//ceck number of channels
    if(sound->vorbisInfo->channels == 1)
        sound->format = AL_FORMAT_MONO16;
    else if (sound->vorbisInfo->channels == 2)
        sound->format = AL_FORMAT_STEREO16;
	else if (sound->vorbisInfo->channels == 4)
		sound->format = alGetEnumValue("AL_FORMAT_QUAD16");
	else if (sound->vorbisInfo->channels == 6)
		sound->format = alGetEnumValue("AL_FORMAT_51CHN16");
	//end of ceck number of channels
        
        
    alGenBuffers(2, sound->buffers);
    check();

	//generate sources
    alGenSources(1, &source);
    check();

	this->sound->filename_path=path;

	/*
    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
	*/

}

void BestSound::SourceOggStream::already_open() {
		//generate sources
    alGenSources(1, &source);
    check();

	/*
    alSource3f(source, AL_POSITION,        0.0, 0.0, 0.0);
    alSource3f(source, AL_VELOCITY,        0.0, 0.0, 0.0);
    alSource3f(source, AL_DIRECTION,       0.0, 0.0, 0.0);
    alSourcef (source, AL_ROLLOFF_FACTOR,  0.0          );
    alSourcei (source, AL_SOURCE_RELATIVE, AL_TRUE      );
	*/
}

void BestSound::SourceOggStream::release()
{
    alSourceStop(source);
    empty();
	alDeleteSources(1, &source);
    check();

    alDeleteBuffers(1, sound->buffers);
    check();

    ov_clear(&sound->oggStream);
	
	/************************************************************************************************************************
		A little bit of cleaning up
	************************************************************************************************************************/
	// Free the memory that we created for the file
	delete[] sound->oggMemoryFile.dataPtr;
	sound->oggMemoryFile.dataPtr = NULL;
}

void BestSound::SourceOggStream::display()
{
	std::cout
        << "version         " << sound->vorbisInfo->version         << "\n"
        << "channels        " << sound->vorbisInfo->channels        << "\n"
        << "rate (hz)       " << sound->vorbisInfo->rate            << "\n"
        << "bitrate upper   " << sound->vorbisInfo->bitrate_upper   << "\n"
        << "bitrate nominal " << sound->vorbisInfo->bitrate_nominal << "\n"
        << "bitrate lower   " << sound->vorbisInfo->bitrate_lower   << "\n"
        << "bitrate window  " << sound->vorbisInfo->bitrate_window  << "\n"
        << "\n"
        << "vendor " << sound->vorbisComment->vendor << "\n";
        
    for(int i = 0; i < sound->vorbisComment->comments; i++)
		std::cout << "   " << sound->vorbisComment->user_comments[i] << "\n";
        
	std::cout << std::endl;
}

bool BestSound::SourceOggStream::playback()
{
    if(playing())
        return true;
        
    if(!stream(sound->buffers[0]))
        return false;
        
    if(!stream(sound->buffers[1]))
        return false;
    
    alSourceQueueBuffers(source, 2,sound->buffers);
    alSourcePlay(source);
    
    return true;
}

bool BestSound::SourceOggStream::playing()
{
    ALenum state;
    
    alGetSourcei(this->source, AL_SOURCE_STATE, &state);
    
    return (state == AL_PLAYING);
}

bool BestSound::SourceOggStream::update()
{
    int processed;
    bool active = true;

    alGetSourcei(source, AL_BUFFERS_PROCESSED, &processed);

    while(processed--)
    {
        ALuint buffer;
        
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();

        active = stream(buffer);

        alSourceQueueBuffers(source, 1, &buffer);
        check();
    }

	//alSourcef(this->source, AL_GAIN,this->gain);
    return active;
}

bool BestSound::SourceOggStream::stream(ALuint buffer)
{
    char pcm[BUFFER_SIZE];
    int  size = 0;
    int  section;
    int  result;

    while(size < BUFFER_SIZE)
    {
        result = ov_read(&sound->oggStream, pcm + size, BUFFER_SIZE - size, 0, 2, 1, &section);
    
        if(result > 0)
            size += result;
        else
            if(result < 0)
                throw errorString(result);
            else
                break;
    }
    
    if(size == 0)
        return false;
        
    alBufferData(buffer, sound->format, pcm, size, sound->vorbisInfo->rate);
    check();
    
    return true;
}

void BestSound::SourceOggStream::empty()
{
    int queued;
    
    alGetSourcei(source, AL_BUFFERS_QUEUED, &queued);
    
    while(queued--)
    {
        ALuint buffer;
    
        alSourceUnqueueBuffers(source, 1, &buffer);
        check();
    }
}




void BestSound::SourceOggStream::check()
{
	int error = alGetError();

	if(error != AL_NO_ERROR)
		throw std::string("OpenAL error was raised.");
}

std::string BestSound::SourceOggStream::errorString(int code)
{
    switch(code)
    {
        case OV_EREAD:
            return std::string("Read from media.");
        case OV_ENOTVORBIS:
            return std::string("Not Vorbis data.");
        case OV_EVERSION:
            return std::string("Vorbis version mismatch.");
        case OV_EBADHEADER:
            return std::string("Invalid Vorbis header.");
        case OV_EFAULT:
            return std::string("Internal logic fault (bug or heap/stack corruption.");
        default:
            return std::string("Unknown Ogg error.");
    }
}

bool BestSound::SourceOggStream::seek(float time)
{
return (ov_time_seek(&sound->oggStream, time) == 0);
}
