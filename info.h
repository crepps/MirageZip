#pragma once

#include "miragezip.h"

namespace Mirage {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for info
	/// </summary>
	public ref class info : public System::Windows::Forms::Form
	{
	private:
	public:
		info()
		{
			InitializeComponent();
			ActiveControl = this->hidden;
			logo->FlatStyle = FlatStyle::Flat;
			logo->FlatAppearance->BorderSize = 0;
		}

	protected:
		~info()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::RichTextBox^ text_info;
	private: System::Windows::Forms::Label^ hidden;

	private: System::Windows::Forms::Button^ logo;
	private: System::Windows::Forms::Label^ divider_top;
	private: System::Windows::Forms::Label^ label_title;
	private: System::Windows::Forms::Label^ label_version;
	private: System::Windows::Forms::Label^ label_copyright;
	private: System::Windows::Forms::LinkLabel^ link_license;
	private: System::Windows::Forms::Label^ divider_bottom;







	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(info::typeid));
			this->text_info = (gcnew System::Windows::Forms::RichTextBox());
			this->hidden = (gcnew System::Windows::Forms::Label());
			this->logo = (gcnew System::Windows::Forms::Button());
			this->divider_top = (gcnew System::Windows::Forms::Label());
			this->label_title = (gcnew System::Windows::Forms::Label());
			this->label_version = (gcnew System::Windows::Forms::Label());
			this->label_copyright = (gcnew System::Windows::Forms::Label());
			this->link_license = (gcnew System::Windows::Forms::LinkLabel());
			this->divider_bottom = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// text_info
			// 
			this->text_info->BackColor = System::Drawing::Color::White;
			this->text_info->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->text_info->Cursor = System::Windows::Forms::Cursors::Cross;
			this->text_info->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_info->Location = System::Drawing::Point(34, 229);
			this->text_info->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->text_info->Name = L"text_info";
			this->text_info->ReadOnly = true;
			this->text_info->Size = System::Drawing::Size(679, 454);
			this->text_info->TabIndex = 0;
			this->text_info->Text = resources->GetString(L"text_info.Text");
			// 
			// hidden
			// 
			this->hidden->AutoSize = true;
			this->hidden->Location = System::Drawing::Point(254, 303);
			this->hidden->Name = L"hidden";
			this->hidden->Size = System::Drawing::Size(0, 13);
			this->hidden->TabIndex = 1;
			this->hidden->Visible = false;
			// 
			// logo
			// 
			this->logo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->logo->FlatAppearance->BorderSize = 0;
			this->logo->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->logo->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->logo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logo.Image")));
			this->logo->Location = System::Drawing::Point(291, 22);
			this->logo->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->logo->Name = L"logo";
			this->logo->Size = System::Drawing::Size(150, 150);
			this->logo->TabIndex = 3;
			this->logo->TabStop = false;
			this->logo->UseVisualStyleBackColor = true;
			// 
			// divider_top
			// 
			this->divider_top->Font = (gcnew System::Drawing::Font(L"MS Gothic", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->divider_top->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->divider_top->Location = System::Drawing::Point(5, -12);
			this->divider_top->Name = L"divider_top";
			this->divider_top->Size = System::Drawing::Size(728, 21);
			this->divider_top->TabIndex = 24;
			this->divider_top->Text = L"______________________________________________________________________";
			this->divider_top->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label_title
			// 
			this->label_title->AutoSize = true;
			this->label_title->Font = (gcnew System::Drawing::Font(L"Courier New", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_title->Location = System::Drawing::Point(94, 79);
			this->label_title->Name = L"label_title";
			this->label_title->Size = System::Drawing::Size(167, 32);
			this->label_title->TabIndex = 25;
			this->label_title->Text = L"MirageZip";
			// 
			// label_version
			// 
			this->label_version->AutoSize = true;
			this->label_version->Font = (gcnew System::Drawing::Font(L"Gadugi", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_version->Location = System::Drawing::Point(522, 65);
			this->label_version->Name = L"label_version";
			this->label_version->Size = System::Drawing::Size(80, 16);
			this->label_version->TabIndex = 26;
			this->label_version->Text = L"Beta Version";
			// 
			// label_copyright
			// 
			this->label_copyright->AutoSize = true;
			this->label_copyright->Font = (gcnew System::Drawing::Font(L"Gadugi", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_copyright->Location = System::Drawing::Point(469, 90);
			this->label_copyright->Name = L"label_copyright";
			this->label_copyright->Size = System::Drawing::Size(195, 16);
			this->label_copyright->TabIndex = 27;
			this->label_copyright->Text = L"Copyright (c) 2024 Kevin Crepps";
			// 
			// link_license
			// 
			this->link_license->Font = (gcnew System::Drawing::Font(L"Gadugi", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_license->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(120)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->link_license->Location = System::Drawing::Point(505, 115);
			this->link_license->Name = L"link_license";
			this->link_license->Size = System::Drawing::Size(112, 20);
			this->link_license->TabIndex = 28;
			this->link_license->TabStop = true;
			this->link_license->Text = L"License";
			this->link_license->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->link_license->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &info::link_license_LinkClicked);
			// 
			// divider_bottom
			// 
			this->divider_bottom->Font = (gcnew System::Drawing::Font(L"MS Gothic", 14.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->divider_bottom->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(240)), static_cast<System::Int32>(static_cast<System::Byte>(240)),
				static_cast<System::Int32>(static_cast<System::Byte>(240)));
			this->divider_bottom->Location = System::Drawing::Point(7, 176);
			this->divider_bottom->Name = L"divider_bottom";
			this->divider_bottom->Size = System::Drawing::Size(728, 21);
			this->divider_bottom->TabIndex = 29;
			this->divider_bottom->Text = L"______________________________________________________________________";
			this->divider_bottom->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(742, 720);
			this->Controls->Add(this->divider_bottom);
			this->Controls->Add(this->link_license);
			this->Controls->Add(this->label_copyright);
			this->Controls->Add(this->label_version);
			this->Controls->Add(this->label_title);
			this->Controls->Add(this->divider_top);
			this->Controls->Add(this->logo);
			this->Controls->Add(this->hidden);
			this->Controls->Add(this->text_info);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"info";
			this->Opacity = 0.99;
			this->Text = L"More";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		private: System::Void link_license_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
		{
			try
			{
				std::string path{ getenv("LOCALAPPDATA") };
				path += "\\MirageZip\\LICENSE";
			
				if (GetFileAttributesA(path.c_str()) == INVALID_FILE_ATTRIBUTES)
				{
					link_license->Text = "(license missing)";
					link_license->Enabled = false;
					return;
				}

				System::Diagnostics::Process::Start(L"notepad.exe", gcnew System::String(path.c_str()));
			}
			catch (std::exception& e)
			{
				link_license->Text = "(failed to open)";
				link_license->Enabled = false;
			}
		}
};
}
