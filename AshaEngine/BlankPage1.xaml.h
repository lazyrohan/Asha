//
// BlankPage1.xaml.h
// Declaration of the BlankPage1 class
//

#pragma once

#include "BlankPage1.g.h"

namespace AshaEngine
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BlankPage1 sealed
	{
	public:
		BlankPage1();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	};
}
