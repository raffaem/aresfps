//This file is a part of "BestSound", 3d cross-platform audio library
//Copyright (C) 2006 Mancuso Raffaele
//To view all terms and condition of use, see bestsound.hpp file in this directory

#include "audioerror.hpp"
BestSound::Error internal_error;

BestSound::Error BestSound::GetError() {
	return internal_error;
}

void BestSound::SetError(ERROR_CODE_ENUM error_code) {
	internal_error.error_code=error_code;
	return;
}
