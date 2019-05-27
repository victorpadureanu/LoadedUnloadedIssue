//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <string>
#include <chrono>

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

std::atomic<int> loaded_count = 0;
int loading_count = 0;
int unloaded_count = 0;

MainPage::MainPage()
{
	InitializeComponent();
	but->Loading += ref new TypedEventHandler<FrameworkElement^, Object^>([=](FrameworkElement^, Object^) {
		loading_count++;
		UpdateCount();
	});
	but->Loaded += ref new RoutedEventHandler([=](Object^, Windows::UI::Xaml::RoutedEventArgs^) {
		loaded_count++;
		UpdateCount();
	});
	but->Unloaded += ref new RoutedEventHandler([=](Object^, Windows::UI::Xaml::RoutedEventArgs^) {
		unloaded_count++;
		UpdateCount();
	});
}

void App2::MainPage::UpdateCount() {
	std::wstring text;
	text += L"Loading count ";
	text += std::to_wstring(loading_count);
	text += L"\nLoaded count ";
	text += std::to_wstring(loaded_count);
	text += L"\nUnloaded count ";
	text += std::to_wstring(unloaded_count);
	Count->Text = ref new String(text.c_str());
}

void App2::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	std::thread x([=]() {
		for (int i = 0; i < 10; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::High, ref new Windows::UI::Core::DispatchedHandler([=]() {
				unsigned int index;
				if (i % 2) {
					if (root->Children->IndexOf(but, &index)) {
						root->Children->RemoveAt(index);
						panel->Children->Append(but);
					}
				}
				else
				{
					if (panel->Children->IndexOf(but, &index)) {
						panel->Children->RemoveAt(index);
						root->Children->Append(but);
					}
				}
			}));
		}
	});

	x.detach();
}
