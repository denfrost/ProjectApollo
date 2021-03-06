// Copyright Brace Yourself Games. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Text/TextLayout.h"
#include "IPropertyTypeCustomization.h"
#include "PropertyHandle.h"

class FBYGTextJustifyCustomization : public IPropertyTypeCustomization
{
public:
	/** Makes a new instance of this detail layout class for a specific detail view requesting it */
	static TSharedRef<class IPropertyTypeCustomization> MakeInstance()
	{
		return MakeShareable(new FBYGTextJustifyCustomization());
	}

	FBYGTextJustifyCustomization()
	{
	}
	
	virtual void CustomizeHeader(TSharedRef<IPropertyHandle> PropertyHandle, class FDetailWidgetRow& HeaderRow, IPropertyTypeCustomizationUtils& CustomizationUtils) override;

	virtual void CustomizeChildren(TSharedRef<IPropertyHandle> PropertyHandle, class IDetailChildrenBuilder& ChildBuilder, IPropertyTypeCustomizationUtils& CustomizationUtils) override;
	
	void HandleCheckStateChanged(ECheckBoxState InCheckboxState, TSharedRef<IPropertyHandle> PropertyHandle, ETextJustify::Type ToAlignment);

	ECheckBoxState GetCheckState(TSharedRef<IPropertyHandle> PropertyHandle, ETextJustify::Type ForAlignment) const;
};
