#pragma once

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
	public:
		info(void)
		{
			InitializeComponent();
			ActiveControl = this->hidden;
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
	private: System::Windows::Forms::Label^ header;

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
			this->header = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// text_info
			// 
			this->text_info->BackColor = System::Drawing::Color::White;
			this->text_info->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->text_info->Cursor = System::Windows::Forms::Cursors::Cross;
			this->text_info->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_info->Location = System::Drawing::Point(31, 82);
			this->text_info->Name = L"text_info";
			this->text_info->ReadOnly = true;
			this->text_info->Size = System::Drawing::Size(679, 454);
			this->text_info->TabIndex = 0;
			this->text_info->Text = resources->GetString(L"text_info.Text");
			// 
			// hidden
			// 
			this->hidden->AutoSize = true;
			this->hidden->Location = System::Drawing::Point(254, 302);
			this->hidden->Name = L"hidden";
			this->hidden->Size = System::Drawing::Size(0, 13);
			this->hidden->TabIndex = 1;
			this->hidden->Visible = false;
			// 
			// header
			// 
			this->header->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->header->Font = (gcnew System::Drawing::Font(L"Lucida Console", 21.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->header->Location = System::Drawing::Point(268, 21);
			this->header->Name = L"header";
			this->header->Size = System::Drawing::Size(193, 41);
			this->header->TabIndex = 2;
			this->header->Text = L"MirageZip";
			this->header->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(742, 566);
			this->Controls->Add(this->header);
			this->Controls->Add(this->hidden);
			this->Controls->Add(this->text_info);
			this->Name = L"info";
			this->Text = L"More";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	};
}
