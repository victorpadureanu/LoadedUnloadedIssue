//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <string>

using namespace App2;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

int loaded_count = 0;
int unloaded_count = 0;

MainPage::MainPage()
{
	InitializeComponent();
	but->Loaded += ref new RoutedEventHandler([=](Object^, Windows::UI::Xaml::RoutedEventArgs^) {
		loaded_count++;
		UpdateCount();
	});
	but->Unloaded += ref new RoutedEventHandler([=](Object^, Windows::UI::Xaml::RoutedEventArgs^) {
		unloaded_count++;
		UpdateCount();
	});
}

void App2::MainPage::Slider_ValueChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::Primitives::RangeBaseValueChangedEventArgs^ e)
{
	unsigned int index;
	int v = e->NewValue;
	
	if(v%2) {
		if( root->Children->IndexOf(but, &index) ) {
			root->Children->RemoveAt(index);
			panel->Children->Append(but);
		}
	}
	else {
		if( panel->Children->IndexOf(but, &index) ) {
			panel->Children->RemoveAt(index);
			root->Children->Append(but);
		}
	}
}

void App2::MainPage::UpdateCount() {
	std::wstring text;
	text += L"Loaded count ";
	text += std::to_wstring(loaded_count);
	text += L"\nUnloaded count ";
	text += std::to_wstring(unloaded_count);
	text += L"\nDifference ";
	text += std::to_wstring(loaded_count-unloaded_count);
	Count->Text = ref new String(text.c_str());
}