// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Widget/BYGRichTextBlock.h"
#include <Framework/Text/ITextDecorator.h>
#include "Settings/BYGRichTextStylesheet.h"
#include <Tests/AutomationEditorCommon.h>
#include <FunctionalTestBase.h>


class FBYGRichTextBlockTestBase : public FFunctionalTestBase
{

public:
	FBYGRichTextBlockTestBase( const FString& InName, const bool bInComplexTask );

	virtual void GetTests(TArray<FString>& OutBeautifiedNames, TArray<FString>& OutTestCommands) const override;
	virtual bool RunTest( const FString& Parameters ) override;

protected:
	struct FBYGTestInstanceBlockData
	{
		const FString Description;
		const FString Input;
		const TArray<FBYGTextBlockInfo> ExpectedTextBlockInfo;
	};

	TMap<FString, FBYGTestInstanceBlockData> TestData;
};

