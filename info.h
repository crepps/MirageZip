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
			this->SuspendLayout();
			// 
			// text_info
			// 
			this->text_info->BackColor = System::Drawing::Color::White;
			this->text_info->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->text_info->Cursor = System::Windows::Forms::Cursors::Cross;
			this->text_info->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->text_info->Location = System::Drawing::Point(34, 189);
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
			// logo
			// 
			this->logo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->logo->FlatAppearance->BorderSize = 0;
			this->logo->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->logo->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->logo->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"logo.Image")));
			this->logo->Location = System::Drawing::Point(293, 21);
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
			// info
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(742, 666);
			this->Controls->Add(this->divider_top);
			this->Controls->Add(this->logo);
			this->Controls->Add(this->hidden);
			this->Controls->Add(this->text_info);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"info";
			this->Opacity = 0.99;
			this->Text = L"More";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
};
}
