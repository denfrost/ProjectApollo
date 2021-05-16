// Copyright 2018 by Nathan "Rama" Iyer. All Rights Reserved.
#include "RamaSaveSystemPrivatePCH.h"
#include "RamaSaveUtility.h"

#include "Runtime/Core/Public/Serialization/ArchiveSaveCompressedProxy.h"
#include "Runtime/Core/Public/Serialization/ArchiveLoadCompressedProxy.h"


bool URamaSaveUtility::IsIllegalForSavingLoading(UClass* Class)
{
	if(!Class) return true;
	
	//Store arbitrary game data in an empty actor that is placed in world
	// or via the use of a UE4 Save Game Object
	return Class->IsChildOf(APlayerController::StaticClass())
			|| Class->IsChildOf(APlayerState::StaticClass())
			|| Class->IsChildOf(AGameState::StaticClass())
			|| Class->IsChildOf(AGameMode::StaticClass());
			 
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Save To Compressed File, by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool URamaSaveUtility::CompressAndWriteToFile(TArray<uint8>& Uncompressed, const FString& FullFilePath)
{
	//~~~ No Data ~~~ 
	if (Uncompressed.Num() <= 0) return false;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//	Write to File


	//~~~~~~~~~~~~~~~~~~~~~~~~~~
	//					Compress
	//~~~ Compress File ~~~
	//tmp compressed data array
	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor(CompressedData, NAME_Zlib);
	
	//Send entire binary array/archive to compressor
	Compressor << Uncompressed;
	
	//send archive serialized data to binary array
	Compressor.Flush();
	
	if (!FFileHelper::SaveArrayToFile(CompressedData, *FullFilePath))
	{
		return false;
	}
	
	//~~~ Clean Up ~~~
	
	//~~~ Free Binary Arrays ~~~
	Compressor.FlushCache();
	CompressedData.Empty();
	Uncompressed.Empty();
	
	return true;
} 

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 	Decompress From File, by Rama
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool URamaSaveUtility::DecompressFromFile(const FString& FullFilePath, TArray<uint8>& Uncompressed)
{
	
	//~~~ File Exists? ~~~
	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*FullFilePath)) return false;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//tmp compressed data array
	TArray<uint8> CompressedData;
	
	if (!FFileHelper::LoadFileToArray(CompressedData, *FullFilePath))
	{
		return false;
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	
	//~~~ Decompress File ~~~
	FArchiveLoadCompressedProxy Decompressor(CompressedData, NAME_Zlib);
	
	//Decompression Error?
	if(Decompressor.GetError())
	{
		return false;
		//~~~~~~~~~~~~
	}
	
	//Send Data from Decompressor to Vibes array
	Decompressor << Uncompressed;

	return true;
}