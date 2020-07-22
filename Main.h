#pragma once

#include "./src/YuLang.h"
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <vcclr.h>

namespace YuLang {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::Win32;
	
	public ref class Main : public System::Windows::Forms::Form
	{
	public:
		Main(void)
		{
			InitializeComponent();
			
			YuInit();

			isDebug = false;
			cbDrill->SelectedIndex = 0;
			cbSample->SelectedIndex = 0;
			tmNewFile_Click( tmNewFile, gcnew System::EventArgs() );
			if ( IO::File::Exists( "YuLang.txt" ) )
				tbSourceCode->LoadFile( "YuLang.txt", RichTextBoxStreamType::PlainText );

			textChanged = true;
			Application::Idle += gcnew System::EventHandler(this, &Main::HighlightSourceCode);
		}

	protected:
		~Main()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  debugToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  tmEditCode;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  tmBuild;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  tmStepOver;

	private: System::Windows::Forms::SplitContainer^  splitContainer3;
	private: System::Windows::Forms::ListView^  listView1;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TreeView^  tvParseTree;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::ListView^  lvTokenList;
	private: System::Windows::Forms::ColumnHeader^  columnHeader13;
	private: System::Windows::Forms::ColumnHeader^  columnHeader14;
	private: System::Windows::Forms::ColumnHeader^  columnHeader15;
	private: System::Windows::Forms::ColumnHeader^  columnHeader16;
	private: System::Windows::Forms::ColumnHeader^  columnHeader17;
	private: System::Windows::Forms::ColumnHeader^  columnHeader18;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::ToolStrip^  toolStrip1;
	private: System::Windows::Forms::ToolStripButton^  tbNewFile;
	private: System::Windows::Forms::ToolStripButton^  tbOpen;
	private: System::Windows::Forms::ToolStripMenuItem^  tmNewFile;
	private: System::Windows::Forms::ToolStripMenuItem^  tmOpen;
	private: System::Windows::Forms::ToolStripMenuItem^  tmSave;
	private: System::Windows::Forms::ToolStripButton^  tbSave;
	private: System::Windows::Forms::ToolStripButton^  tbBuild;
	private: System::Windows::Forms::ToolStripButton^  tbRun;
	private: System::Windows::Forms::ToolStripButton^  tbStepOver;

	private: System::Windows::Forms::ToolStripMenuItem^  tmRun;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Panel^  panel2;

	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::RichTextBox^  tbSourceCode;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::ListView^  lvByteCodes;
	private: System::Windows::Forms::ColumnHeader^  address;
	private: System::Windows::Forms::ColumnHeader^  instruction;
	private: System::Windows::Forms::ColumnHeader^  Value;
	private: System::Windows::Forms::ColumnHeader^  name;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::ListView^  lvDataSegment;
	private: System::Windows::Forms::ColumnHeader^  columnHeader1;
	private: System::Windows::Forms::ColumnHeader^  columnHeader24;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Panel^  panel6;
	private: System::Windows::Forms::Label^  lbStackSegmentInfo;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::ListView^  lvOperandStack;
	private: System::Windows::Forms::ColumnHeader^  columnHeader2;
	private: System::Windows::Forms::ColumnHeader^  columnHeader4;
	private: System::Windows::Forms::ListView^  lvStackSegment;
	private: System::Windows::Forms::ColumnHeader^  columnHeader3;
	private: System::Windows::Forms::ColumnHeader^  columnHeader6;
	private: System::Windows::Forms::TextBox^  tbDrill;
	private: System::Windows::Forms::ComboBox^  cbDrill;

	private: System::Windows::Forms::TextBox^  tbDrill5;
	private: System::Windows::Forms::TextBox^  tbDrill4;
	private: System::Windows::Forms::TextBox^  tbDrill3;
	private: System::Windows::Forms::TextBox^  tbDrill2;
	private: System::Windows::Forms::TextBox^  tbDrill1;
	private: System::Windows::Forms::TextBox^  tbBasicTemplete;
	private: System::Windows::Forms::ToolStripMenuItem^  tmExit;


	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
private: System::Windows::Forms::ToolStripButton^  tbDebug;

private: System::Windows::Forms::ToolStripButton^  tbContinue;



private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem1;
private: System::Windows::Forms::ToolStripMenuItem^  tmDebug;


private: System::Windows::Forms::ToolStripMenuItem^  tmContinue;
private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator4;
private: System::Windows::Forms::ColumnHeader^  BP;
private: System::Windows::Forms::ImageList^  imageList1;
private: System::Windows::Forms::TabPage^  tabPage4;
private: System::Windows::Forms::TextBox^  tbSampleWhile;

private: System::Windows::Forms::ComboBox^  cbSample;

private: System::Windows::Forms::TextBox^  tbSample;
private: System::Windows::Forms::TextBox^  tbSampleDevideBy0;






private: System::Windows::Forms::TextBox^  tbSampleMemoryAccess;



private: System::Windows::Forms::TextBox^  tbSampleOverflow;



private: System::Windows::Forms::TextBox^  tbSampleFactorial;



private: System::Windows::Forms::TextBox^  tbSampleArray;



private: System::Windows::Forms::TextBox^  tbSampleDef;

private: System::Windows::Forms::TextBox^  tbSampleIf;







private: System::Windows::Forms::Button^  btnRunSample;
private: System::Windows::Forms::TextBox^  tbSampleSort;


private: System::Windows::Forms::TextBox^  tbOutput;
private: System::Windows::Forms::ToolStripSeparator^  toolStripMenuItem2;













	private: System::ComponentModel::IContainer^  components;

	#pragma region Windows Form Designer generated code
	void InitializeComponent(void)
	{
		this->components = (gcnew System::ComponentModel::Container());
		System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Main::typeid));
		System::Windows::Forms::ListViewItem^  listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L""));
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmNewFile = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmOpen = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmSave = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmExit = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->debugToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmEditCode = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tmRun = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tmBuild = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tmDebug = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmStepOver = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->tmContinue = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->splitContainer3 = (gcnew System::Windows::Forms::SplitContainer());
		this->tbBasicTemplete = (gcnew System::Windows::Forms::TextBox());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->tbSourceCode = (gcnew System::Windows::Forms::RichTextBox());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->panel2 = (gcnew System::Windows::Forms::Panel());
		this->tbOutput = (gcnew System::Windows::Forms::TextBox());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->listView1 = (gcnew System::Windows::Forms::ListView());
		this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
		this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
		this->tbSampleSort = (gcnew System::Windows::Forms::TextBox());
		this->btnRunSample = (gcnew System::Windows::Forms::Button());
		this->tbSampleDevideBy0 = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleMemoryAccess = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleOverflow = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleFactorial = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleArray = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleDef = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleIf = (gcnew System::Windows::Forms::TextBox());
		this->tbSampleWhile = (gcnew System::Windows::Forms::TextBox());
		this->cbSample = (gcnew System::Windows::Forms::ComboBox());
		this->tbSample = (gcnew System::Windows::Forms::TextBox());
		this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
		this->tbDrill5 = (gcnew System::Windows::Forms::TextBox());
		this->tbDrill4 = (gcnew System::Windows::Forms::TextBox());
		this->tbDrill3 = (gcnew System::Windows::Forms::TextBox());
		this->tbDrill2 = (gcnew System::Windows::Forms::TextBox());
		this->tbDrill1 = (gcnew System::Windows::Forms::TextBox());
		this->cbDrill = (gcnew System::Windows::Forms::ComboBox());
		this->tbDrill = (gcnew System::Windows::Forms::TextBox());
		this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
		this->tvParseTree = (gcnew System::Windows::Forms::TreeView());
		this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
		this->lvTokenList = (gcnew System::Windows::Forms::ListView());
		this->columnHeader13 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader14 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader15 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader16 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader17 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader18 = (gcnew System::Windows::Forms::ColumnHeader());
		this->toolStrip1 = (gcnew System::Windows::Forms::ToolStrip());
		this->tbNewFile = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbOpen = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbSave = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tbRun = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripSeparator4 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tbBuild = (gcnew System::Windows::Forms::ToolStripButton());
		this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
		this->tbDebug = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbStepOver = (gcnew System::Windows::Forms::ToolStripButton());
		this->tbContinue = (gcnew System::Windows::Forms::ToolStripButton());
		this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
		this->panel3 = (gcnew System::Windows::Forms::Panel());
		this->lvByteCodes = (gcnew System::Windows::Forms::ListView());
		this->BP = (gcnew System::Windows::Forms::ColumnHeader());
		this->address = (gcnew System::Windows::Forms::ColumnHeader());
		this->instruction = (gcnew System::Windows::Forms::ColumnHeader());
		this->Value = (gcnew System::Windows::Forms::ColumnHeader());
		this->name = (gcnew System::Windows::Forms::ColumnHeader());
		this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->panel4 = (gcnew System::Windows::Forms::Panel());
		this->lvOperandStack = (gcnew System::Windows::Forms::ListView());
		this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader4 = (gcnew System::Windows::Forms::ColumnHeader());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->panel5 = (gcnew System::Windows::Forms::Panel());
		this->lvDataSegment = (gcnew System::Windows::Forms::ListView());
		this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader24 = (gcnew System::Windows::Forms::ColumnHeader());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->panel6 = (gcnew System::Windows::Forms::Panel());
		this->lvStackSegment = (gcnew System::Windows::Forms::ListView());
		this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
		this->columnHeader6 = (gcnew System::Windows::Forms::ColumnHeader());
		this->lbStackSegmentInfo = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->menuStrip1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->BeginInit();
		this->splitContainer3->Panel1->SuspendLayout();
		this->splitContainer3->Panel2->SuspendLayout();
		this->splitContainer3->SuspendLayout();
		this->panel1->SuspendLayout();
		this->panel2->SuspendLayout();
		this->tabControl1->SuspendLayout();
		this->tabPage4->SuspendLayout();
		this->tabPage3->SuspendLayout();
		this->tabPage1->SuspendLayout();
		this->tabPage2->SuspendLayout();
		this->toolStrip1->SuspendLayout();
		this->panel3->SuspendLayout();
		this->panel4->SuspendLayout();
		this->panel5->SuspendLayout();
		this->panel6->SuspendLayout();
		this->SuspendLayout();
		// 
		// menuStrip1
		// 
		this->menuStrip1->BackColor = System::Drawing::SystemColors::Window;
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->fileToolStripMenuItem,
				this->debugToolStripMenuItem
		});
		this->menuStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1480, 24);
		this->menuStrip1->TabIndex = 1;
		this->menuStrip1->Text = L"menuStrip1";
		// 
		// fileToolStripMenuItem
		// 
		this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
			this->tmNewFile,
				this->tmOpen, this->tmSave, this->tmExit
		});
		this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
		this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
		this->fileToolStripMenuItem->Text = L"File";
		// 
		// tmNewFile
		// 
		this->tmNewFile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmNewFile.Image")));
		this->tmNewFile->Name = L"tmNewFile";
		this->tmNewFile->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
		this->tmNewFile->Size = System::Drawing::Size(163, 22);
		this->tmNewFile->Text = L"New File";
		this->tmNewFile->Click += gcnew System::EventHandler(this, &Main::tmNewFile_Click);
		// 
		// tmOpen
		// 
		this->tmOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmOpen.Image")));
		this->tmOpen->Name = L"tmOpen";
		this->tmOpen->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::O));
		this->tmOpen->Size = System::Drawing::Size(163, 22);
		this->tmOpen->Text = L"Open";
		this->tmOpen->Click += gcnew System::EventHandler(this, &Main::tmOpen_Click);
		// 
		// tmSave
		// 
		this->tmSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmSave.Image")));
		this->tmSave->Name = L"tmSave";
		this->tmSave->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
		this->tmSave->Size = System::Drawing::Size(163, 22);
		this->tmSave->Text = L"Save";
		this->tmSave->Click += gcnew System::EventHandler(this, &Main::tmSave_Click);
		// 
		// tmExit
		// 
		this->tmExit->Name = L"tmExit";
		this->tmExit->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
		this->tmExit->Size = System::Drawing::Size(163, 22);
		this->tmExit->Text = L"Exit";
		this->tmExit->Click += gcnew System::EventHandler(this, &Main::tmExit_Click);
		// 
		// debugToolStripMenuItem
		// 
		this->debugToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(9) {
			this->tmEditCode,
				this->toolStripSeparator1, this->tmRun, this->toolStripMenuItem2, this->tmBuild, this->toolStripMenuItem1, this->tmDebug, this->tmStepOver,
				this->tmContinue
		});
		this->debugToolStripMenuItem->Name = L"debugToolStripMenuItem";
		this->debugToolStripMenuItem->Size = System::Drawing::Size(55, 20);
		this->debugToolStripMenuItem->Text = L"Debug";
		// 
		// tmEditCode
		// 
		this->tmEditCode->Name = L"tmEditCode";
		this->tmEditCode->ShortcutKeys = System::Windows::Forms::Keys::F4;
		this->tmEditCode->Size = System::Drawing::Size(154, 22);
		this->tmEditCode->Text = L"Edit Code";
		this->tmEditCode->Visible = false;
		this->tmEditCode->Click += gcnew System::EventHandler(this, &Main::tmEditCode_Click);
		// 
		// toolStripSeparator1
		// 
		this->toolStripSeparator1->Name = L"toolStripSeparator1";
		this->toolStripSeparator1->Size = System::Drawing::Size(151, 6);
		this->toolStripSeparator1->Visible = false;
		// 
		// tmRun
		// 
		this->tmRun->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmRun.Image")));
		this->tmRun->Name = L"tmRun";
		this->tmRun->ShortcutKeys = System::Windows::Forms::Keys::F5;
		this->tmRun->Size = System::Drawing::Size(154, 22);
		this->tmRun->Text = L"Run";
		this->tmRun->Click += gcnew System::EventHandler(this, &Main::tmRun_Click);
		// 
		// toolStripMenuItem2
		// 
		this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
		this->toolStripMenuItem2->Size = System::Drawing::Size(151, 6);
		// 
		// tmBuild
		// 
		this->tmBuild->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmBuild.Image")));
		this->tmBuild->Name = L"tmBuild";
		this->tmBuild->ShortcutKeys = System::Windows::Forms::Keys::F6;
		this->tmBuild->Size = System::Drawing::Size(154, 22);
		this->tmBuild->Text = L"Build";
		this->tmBuild->Click += gcnew System::EventHandler(this, &Main::tmBuild_Click);
		// 
		// toolStripMenuItem1
		// 
		this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
		this->toolStripMenuItem1->Size = System::Drawing::Size(151, 6);
		// 
		// tmDebug
		// 
		this->tmDebug->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmDebug.Image")));
		this->tmDebug->Name = L"tmDebug";
		this->tmDebug->ShortcutKeys = System::Windows::Forms::Keys::F9;
		this->tmDebug->Size = System::Drawing::Size(154, 22);
		this->tmDebug->Text = L"Debug";
		this->tmDebug->Click += gcnew System::EventHandler(this, &Main::tmDebug_Click);
		// 
		// tmStepOver
		// 
		this->tmStepOver->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmStepOver.Image")));
		this->tmStepOver->Name = L"tmStepOver";
		this->tmStepOver->ShortcutKeys = System::Windows::Forms::Keys::F10;
		this->tmStepOver->Size = System::Drawing::Size(154, 22);
		this->tmStepOver->Text = L"Step Over";
		this->tmStepOver->Click += gcnew System::EventHandler(this, &Main::tmStepOver_Click);
		// 
		// tmContinue
		// 
		this->tmContinue->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tmContinue.Image")));
		this->tmContinue->Name = L"tmContinue";
		this->tmContinue->ShortcutKeys = System::Windows::Forms::Keys::F11;
		this->tmContinue->Size = System::Drawing::Size(154, 22);
		this->tmContinue->Text = L"Continue";
		this->tmContinue->Click += gcnew System::EventHandler(this, &Main::tmContinue_Click);
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->BackColor = System::Drawing::SystemColors::WindowText;
		this->label1->Location = System::Drawing::Point(1369, 9);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(0, 12);
		this->label1->TabIndex = 7;
		// 
		// splitContainer3
		// 
		this->splitContainer3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->splitContainer3->Location = System::Drawing::Point(407, 61);
		this->splitContainer3->Name = L"splitContainer3";
		this->splitContainer3->Orientation = System::Windows::Forms::Orientation::Horizontal;
		// 
		// splitContainer3.Panel1
		// 
		this->splitContainer3->Panel1->BackColor = System::Drawing::SystemColors::ControlLight;
		this->splitContainer3->Panel1->Controls->Add(this->tbBasicTemplete);
		this->splitContainer3->Panel1->Controls->Add(this->panel1);
		this->splitContainer3->Panel1->Controls->Add(this->label7);
		this->splitContainer3->Panel1->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		// 
		// splitContainer3.Panel2
		// 
		this->splitContainer3->Panel2->BackColor = System::Drawing::SystemColors::ControlLight;
		this->splitContainer3->Panel2->Controls->Add(this->panel2);
		this->splitContainer3->Panel2->Controls->Add(this->label6);
		this->splitContainer3->Panel2->Controls->Add(this->listView1);
		this->splitContainer3->Panel2->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		this->splitContainer3->Size = System::Drawing::Size(349, 716);
		this->splitContainer3->SplitterDistance = 542;
		this->splitContainer3->SplitterWidth = 10;
		this->splitContainer3->TabIndex = 10;
		this->splitContainer3->TabStop = false;
		// 
		// tbBasicTemplete
		// 
		this->tbBasicTemplete->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->tbBasicTemplete->Location = System::Drawing::Point(112, 2);
		this->tbBasicTemplete->Name = L"tbBasicTemplete";
		this->tbBasicTemplete->Size = System::Drawing::Size(31, 21);
		this->tbBasicTemplete->TabIndex = 28;
		this->tbBasicTemplete->Text = L"def main() {\r\n\t\r\n}";
		this->tbBasicTemplete->Visible = false;
		// 
		// panel1
		// 
		this->panel1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->panel1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
			static_cast<System::Int32>(static_cast<System::Byte>(30)));
		this->panel1->Controls->Add(this->tbSourceCode);
		this->panel1->Location = System::Drawing::Point(1, 26);
		this->panel1->Name = L"panel1";
		this->panel1->Padding = System::Windows::Forms::Padding(5, 3, 0, 0);
		this->panel1->Size = System::Drawing::Size(348, 516);
		this->panel1->TabIndex = 7;
		// 
		// tbSourceCode
		// 
		this->tbSourceCode->AcceptsTab = true;
		this->tbSourceCode->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->tbSourceCode->BackColor = System::Drawing::Color::Black;
		this->tbSourceCode->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->tbSourceCode->DetectUrls = false;
		this->tbSourceCode->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->tbSourceCode->ForeColor = System::Drawing::Color::WhiteSmoke;
		this->tbSourceCode->ImeMode = System::Windows::Forms::ImeMode::NoControl;
		this->tbSourceCode->Location = System::Drawing::Point(5, 1);
		this->tbSourceCode->Name = L"tbSourceCode";
		this->tbSourceCode->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedVertical;
		this->tbSourceCode->Size = System::Drawing::Size(342, 514);
		this->tbSourceCode->TabIndex = 9;
		this->tbSourceCode->Text = L"";
		this->tbSourceCode->WordWrap = false;
		this->tbSourceCode->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::tbSourceCode_KeyDown);
		this->tbSourceCode->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &Main::tbSourceCode_KeyUp);
		// 
		// label7
		// 
		this->label7->BackColor = System::Drawing::SystemColors::Window;
		this->label7->Dock = System::Windows::Forms::DockStyle::Top;
		this->label7->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label7->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label7->Location = System::Drawing::Point(1, 0);
		this->label7->Name = L"label7";
		this->label7->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label7->Size = System::Drawing::Size(348, 26);
		this->label7->TabIndex = 6;
		this->label7->Text = L"Source Code";
		// 
		// panel2
		// 
		this->panel2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(30)), static_cast<System::Int32>(static_cast<System::Byte>(30)),
			static_cast<System::Int32>(static_cast<System::Byte>(30)));
		this->panel2->Controls->Add(this->tbOutput);
		this->panel2->Location = System::Drawing::Point(1, 29);
		this->panel2->Name = L"panel2";
		this->panel2->Size = System::Drawing::Size(348, 135);
		this->panel2->TabIndex = 6;
		// 
		// tbOutput
		// 
		this->tbOutput->AcceptsReturn = true;
		this->tbOutput->AcceptsTab = true;
		this->tbOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->tbOutput->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(20)), static_cast<System::Int32>(static_cast<System::Byte>(20)),
			static_cast<System::Int32>(static_cast<System::Byte>(20)));
		this->tbOutput->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->tbOutput->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->tbOutput->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(224)), static_cast<System::Int32>(static_cast<System::Byte>(224)),
			static_cast<System::Int32>(static_cast<System::Byte>(224)));
		this->tbOutput->Location = System::Drawing::Point(5, 1);
		this->tbOutput->Multiline = true;
		this->tbOutput->Name = L"tbOutput";
		this->tbOutput->ReadOnly = true;
		this->tbOutput->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->tbOutput->Size = System::Drawing::Size(342, 127);
		this->tbOutput->TabIndex = 0;
		// 
		// label6
		// 
		this->label6->BackColor = System::Drawing::SystemColors::Window;
		this->label6->Dock = System::Windows::Forms::DockStyle::Top;
		this->label6->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label6->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label6->Location = System::Drawing::Point(1, 0);
		this->label6->Name = L"label6";
		this->label6->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label6->Size = System::Drawing::Size(348, 26);
		this->label6->TabIndex = 5;
		this->label6->Text = L"Output";
		// 
		// listView1
		// 
		this->listView1->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->listView1->Dock = System::Windows::Forms::DockStyle::Fill;
		this->listView1->Location = System::Drawing::Point(1, 0);
		this->listView1->Name = L"listView1";
		this->listView1->Size = System::Drawing::Size(348, 164);
		this->listView1->TabIndex = 0;
		this->listView1->UseCompatibleStateImageBehavior = false;
		// 
		// tabControl1
		// 
		this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left));
		this->tabControl1->Controls->Add(this->tabPage4);
		this->tabControl1->Controls->Add(this->tabPage3);
		this->tabControl1->Controls->Add(this->tabPage1);
		this->tabControl1->Controls->Add(this->tabPage2);
		this->tabControl1->Location = System::Drawing::Point(12, 61);
		this->tabControl1->Multiline = true;
		this->tabControl1->Name = L"tabControl1";
		this->tabControl1->SelectedIndex = 0;
		this->tabControl1->Size = System::Drawing::Size(383, 716);
		this->tabControl1->TabIndex = 12;
		// 
		// tabPage4
		// 
		this->tabPage4->Controls->Add(this->tbSampleSort);
		this->tabPage4->Controls->Add(this->btnRunSample);
		this->tabPage4->Controls->Add(this->tbSampleDevideBy0);
		this->tabPage4->Controls->Add(this->tbSampleMemoryAccess);
		this->tabPage4->Controls->Add(this->tbSampleOverflow);
		this->tabPage4->Controls->Add(this->tbSampleFactorial);
		this->tabPage4->Controls->Add(this->tbSampleArray);
		this->tabPage4->Controls->Add(this->tbSampleDef);
		this->tabPage4->Controls->Add(this->tbSampleIf);
		this->tabPage4->Controls->Add(this->tbSampleWhile);
		this->tabPage4->Controls->Add(this->cbSample);
		this->tabPage4->Controls->Add(this->tbSample);
		this->tabPage4->Location = System::Drawing::Point(4, 22);
		this->tabPage4->Name = L"tabPage4";
		this->tabPage4->Padding = System::Windows::Forms::Padding(3);
		this->tabPage4->Size = System::Drawing::Size(375, 690);
		this->tabPage4->TabIndex = 3;
		this->tabPage4->Text = L"Samples";
		this->tabPage4->UseVisualStyleBackColor = true;
		// 
		// tbSampleSort
		// 
		this->tbSampleSort->Location = System::Drawing::Point(317, 173);
		this->tbSampleSort->Name = L"tbSampleSort";
		this->tbSampleSort->Size = System::Drawing::Size(31, 21);
		this->tbSampleSort->TabIndex = 38;
		this->tbSampleSort->Text = resources->GetString(L"tbSampleSort.Text");
		this->tbSampleSort->Visible = false;
		// 
		// btnRunSample
		// 
		this->btnRunSample->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnRunSample.Image")));
		this->btnRunSample->Location = System::Drawing::Point(356, 1);
		this->btnRunSample->Name = L"btnRunSample";
		this->btnRunSample->Size = System::Drawing::Size(18, 22);
		this->btnRunSample->TabIndex = 37;
		this->btnRunSample->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
		this->btnRunSample->UseVisualStyleBackColor = true;
		this->btnRunSample->Click += gcnew System::EventHandler(this, &Main::btnRunSample_Click);
		// 
		// tbSampleDevideBy0
		// 
		this->tbSampleDevideBy0->Location = System::Drawing::Point(317, 254);
		this->tbSampleDevideBy0->Name = L"tbSampleDevideBy0";
		this->tbSampleDevideBy0->Size = System::Drawing::Size(31, 21);
		this->tbSampleDevideBy0->TabIndex = 36;
		this->tbSampleDevideBy0->Text = L"def main() {\r\n\tvar a = 1\r\n\tvar b = 0\r\n\tprint( a / b )\r\n}";
		this->tbSampleDevideBy0->Visible = false;
		// 
		// tbSampleMemoryAccess
		// 
		this->tbSampleMemoryAccess->Location = System::Drawing::Point(317, 227);
		this->tbSampleMemoryAccess->Name = L"tbSampleMemoryAccess";
		this->tbSampleMemoryAccess->Size = System::Drawing::Size(31, 21);
		this->tbSampleMemoryAccess->TabIndex = 35;
		this->tbSampleMemoryAccess->Text = L"arr a[4096]\r\n\r\ndef main() {\r\n\tvar i = 4096\r\n\ta[i] = 7\r\n}";
		this->tbSampleMemoryAccess->Visible = false;
		// 
		// tbSampleOverflow
		// 
		this->tbSampleOverflow->Location = System::Drawing::Point(317, 200);
		this->tbSampleOverflow->Name = L"tbSampleOverflow";
		this->tbSampleOverflow->Size = System::Drawing::Size(31, 21);
		this->tbSampleOverflow->TabIndex = 34;
		this->tbSampleOverflow->Text = L"def stackOverflow( n ) {\r\n\tstackOverflow( n )\r\n}\r\n\r\ndef main() {\r\n\tstackOverflow("
			L" 5 )\r\n}\r\n";
		this->tbSampleOverflow->Visible = false;
		// 
		// tbSampleFactorial
		// 
		this->tbSampleFactorial->Location = System::Drawing::Point(317, 146);
		this->tbSampleFactorial->Name = L"tbSampleFactorial";
		this->tbSampleFactorial->Size = System::Drawing::Size(31, 21);
		this->tbSampleFactorial->TabIndex = 33;
		this->tbSampleFactorial->Text = L"def factorial( n ) {\r\n\tif ( n <= 1 ) {\r\n\t\treturn 1\r\n\t}\r\n\treturn n * factorial( n "
			L"- 1 )\r\n}\r\n\r\ndef main() {\r\n\tprint( factorial( 5 ) )\r\n}";
		this->tbSampleFactorial->Visible = false;
		// 
		// tbSampleArray
		// 
		this->tbSampleArray->Location = System::Drawing::Point(317, 119);
		this->tbSampleArray->Name = L"tbSampleArray";
		this->tbSampleArray->Size = System::Drawing::Size(31, 21);
		this->tbSampleArray->TabIndex = 32;
		this->tbSampleArray->Text = resources->GetString(L"tbSampleArray.Text");
		this->tbSampleArray->Visible = false;
		// 
		// tbSampleDef
		// 
		this->tbSampleDef->Location = System::Drawing::Point(317, 92);
		this->tbSampleDef->Name = L"tbSampleDef";
		this->tbSampleDef->Size = System::Drawing::Size(31, 21);
		this->tbSampleDef->TabIndex = 31;
		this->tbSampleDef->Text = resources->GetString(L"tbSampleDef.Text");
		this->tbSampleDef->Visible = false;
		// 
		// tbSampleIf
		// 
		this->tbSampleIf->Location = System::Drawing::Point(317, 65);
		this->tbSampleIf->Name = L"tbSampleIf";
		this->tbSampleIf->Size = System::Drawing::Size(31, 21);
		this->tbSampleIf->TabIndex = 30;
		this->tbSampleIf->Text = resources->GetString(L"tbSampleIf.Text");
		this->tbSampleIf->Visible = false;
		// 
		// tbSampleWhile
		// 
		this->tbSampleWhile->Location = System::Drawing::Point(317, 38);
		this->tbSampleWhile->Name = L"tbSampleWhile";
		this->tbSampleWhile->Size = System::Drawing::Size(31, 21);
		this->tbSampleWhile->TabIndex = 28;
		this->tbSampleWhile->Text = resources->GetString(L"tbSampleWhile.Text");
		this->tbSampleWhile->Visible = false;
		// 
		// cbSample
		// 
		this->cbSample->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->cbSample->BackColor = System::Drawing::SystemColors::Window;
		this->cbSample->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbSample->FormattingEnabled = true;
		this->cbSample->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
			L"0. 반복문 (while, break, continue)", L"1. 조건문 (if, elif, else)",
				L"2. 함수 (def, return)", L"3. 배열 (arr)", L"4. 팩토리얼 (재귀함수)", L"5. 버블정렬", L"6. 런타임 에러 (스택 오버플로우)", L"7. 런타임 에러 (잘못된 메모리 접근)", L"8. 런타임 에러 (0으로 나눔)"
		});
		this->cbSample->Location = System::Drawing::Point(2, 2);
		this->cbSample->Name = L"cbSample";
		this->cbSample->Size = System::Drawing::Size(354, 20);
		this->cbSample->TabIndex = 2;
		this->cbSample->TabStop = false;
		this->cbSample->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::cbSample_SelectedIndexChanged);
		// 
		// tbSample
		// 
		this->tbSample->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->tbSample->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->tbSample->Font = (gcnew System::Drawing::Font(L"Consolas", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->tbSample->Location = System::Drawing::Point(2, 23);
		this->tbSample->Multiline = true;
		this->tbSample->Name = L"tbSample";
		this->tbSample->ReadOnly = true;
		this->tbSample->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->tbSample->Size = System::Drawing::Size(371, 665);
		this->tbSample->TabIndex = 29;
		this->tbSample->TabStop = false;
		// 
		// tabPage3
		// 
		this->tabPage3->Controls->Add(this->tbDrill5);
		this->tabPage3->Controls->Add(this->tbDrill4);
		this->tabPage3->Controls->Add(this->tbDrill3);
		this->tabPage3->Controls->Add(this->tbDrill2);
		this->tabPage3->Controls->Add(this->tbDrill1);
		this->tabPage3->Controls->Add(this->cbDrill);
		this->tabPage3->Controls->Add(this->tbDrill);
		this->tabPage3->Location = System::Drawing::Point(4, 22);
		this->tabPage3->Name = L"tabPage3";
		this->tabPage3->Padding = System::Windows::Forms::Padding(3);
		this->tabPage3->Size = System::Drawing::Size(375, 690);
		this->tabPage3->TabIndex = 2;
		this->tabPage3->Text = L"Programmer\'s Way";
		this->tabPage3->UseVisualStyleBackColor = true;
		// 
		// tbDrill5
		// 
		this->tbDrill5->Location = System::Drawing::Point(248, 110);
		this->tbDrill5->Name = L"tbDrill5";
		this->tbDrill5->Size = System::Drawing::Size(31, 21);
		this->tbDrill5->TabIndex = 26;
		this->tbDrill5->Text = resources->GetString(L"tbDrill5.Text");
		this->tbDrill5->Visible = false;
		// 
		// tbDrill4
		// 
		this->tbDrill4->Location = System::Drawing::Point(211, 110);
		this->tbDrill4->Name = L"tbDrill4";
		this->tbDrill4->Size = System::Drawing::Size(31, 21);
		this->tbDrill4->TabIndex = 25;
		this->tbDrill4->Text = resources->GetString(L"tbDrill4.Text");
		this->tbDrill4->Visible = false;
		// 
		// tbDrill3
		// 
		this->tbDrill3->Location = System::Drawing::Point(174, 110);
		this->tbDrill3->Name = L"tbDrill3";
		this->tbDrill3->Size = System::Drawing::Size(31, 21);
		this->tbDrill3->TabIndex = 24;
		this->tbDrill3->Text = resources->GetString(L"tbDrill3.Text");
		this->tbDrill3->Visible = false;
		// 
		// tbDrill2
		// 
		this->tbDrill2->Location = System::Drawing::Point(137, 110);
		this->tbDrill2->Name = L"tbDrill2";
		this->tbDrill2->Size = System::Drawing::Size(31, 21);
		this->tbDrill2->TabIndex = 23;
		this->tbDrill2->Text = resources->GetString(L"tbDrill2.Text");
		this->tbDrill2->Visible = false;
		// 
		// tbDrill1
		// 
		this->tbDrill1->Location = System::Drawing::Point(100, 110);
		this->tbDrill1->Name = L"tbDrill1";
		this->tbDrill1->Size = System::Drawing::Size(31, 21);
		this->tbDrill1->TabIndex = 22;
		this->tbDrill1->Text = resources->GetString(L"tbDrill1.Text");
		this->tbDrill1->Visible = false;
		// 
		// cbDrill
		// 
		this->cbDrill->BackColor = System::Drawing::SystemColors::Window;
		this->cbDrill->Dock = System::Windows::Forms::DockStyle::Top;
		this->cbDrill->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cbDrill->FormattingEnabled = true;
		this->cbDrill->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
			L"1. 첫번째 문제 모음 (반복문)", L"2. 세번째 문제 모음 (배열)", L"3. 마방진",
				L"4. 개미수열", L"5. 파스칼의 삼각형, 소수 구하기"
		});
		this->cbDrill->Location = System::Drawing::Point(3, 3);
		this->cbDrill->Name = L"cbDrill";
		this->cbDrill->Size = System::Drawing::Size(369, 20);
		this->cbDrill->TabIndex = 1;
		this->cbDrill->TabStop = false;
		this->cbDrill->SelectedIndexChanged += gcnew System::EventHandler(this, &Main::comboBox1_SelectedIndexChanged);
		// 
		// tbDrill
		// 
		this->tbDrill->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->tbDrill->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->tbDrill->Font = (gcnew System::Drawing::Font(L"Malgun Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(129)));
		this->tbDrill->Location = System::Drawing::Point(2, 24);
		this->tbDrill->Multiline = true;
		this->tbDrill->Name = L"tbDrill";
		this->tbDrill->ReadOnly = true;
		this->tbDrill->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
		this->tbDrill->Size = System::Drawing::Size(371, 664);
		this->tbDrill->TabIndex = 0;
		// 
		// tabPage1
		// 
		this->tabPage1->Controls->Add(this->tvParseTree);
		this->tabPage1->Location = System::Drawing::Point(4, 22);
		this->tabPage1->Name = L"tabPage1";
		this->tabPage1->Padding = System::Windows::Forms::Padding(3);
		this->tabPage1->Size = System::Drawing::Size(375, 690);
		this->tabPage1->TabIndex = 0;
		this->tabPage1->Text = L"Syntax Tree";
		this->tabPage1->UseVisualStyleBackColor = true;
		// 
		// tvParseTree
		// 
		this->tvParseTree->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->tvParseTree->Dock = System::Windows::Forms::DockStyle::Fill;
		this->tvParseTree->Font = (gcnew System::Drawing::Font(L"Consolas", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->tvParseTree->FullRowSelect = true;
		this->tvParseTree->Location = System::Drawing::Point(3, 3);
		this->tvParseTree->Name = L"tvParseTree";
		this->tvParseTree->ShowRootLines = false;
		this->tvParseTree->Size = System::Drawing::Size(369, 684);
		this->tvParseTree->TabIndex = 12;
		this->tvParseTree->TabStop = false;
		// 
		// tabPage2
		// 
		this->tabPage2->Controls->Add(this->lvTokenList);
		this->tabPage2->Location = System::Drawing::Point(4, 22);
		this->tabPage2->Name = L"tabPage2";
		this->tabPage2->Padding = System::Windows::Forms::Padding(3);
		this->tabPage2->Size = System::Drawing::Size(375, 690);
		this->tabPage2->TabIndex = 1;
		this->tabPage2->Text = L"Token List";
		this->tabPage2->UseVisualStyleBackColor = true;
		// 
		// lvTokenList
		// 
		this->lvTokenList->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->lvTokenList->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(6) {
			this->columnHeader13,
				this->columnHeader14, this->columnHeader15, this->columnHeader16, this->columnHeader17, this->columnHeader18
		});
		this->lvTokenList->Dock = System::Windows::Forms::DockStyle::Fill;
		this->lvTokenList->Font = (gcnew System::Drawing::Font(L"Malgun Gothic", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(129)));
		this->lvTokenList->FullRowSelect = true;
		this->lvTokenList->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lvTokenList->HideSelection = false;
		this->lvTokenList->Location = System::Drawing::Point(3, 3);
		this->lvTokenList->MultiSelect = false;
		this->lvTokenList->Name = L"lvTokenList";
		this->lvTokenList->Size = System::Drawing::Size(369, 684);
		this->lvTokenList->TabIndex = 4;
		this->lvTokenList->TabStop = false;
		this->lvTokenList->UseCompatibleStateImageBehavior = false;
		this->lvTokenList->View = System::Windows::Forms::View::Details;
		// 
		// columnHeader13
		// 
		this->columnHeader13->Text = L"No";
		this->columnHeader13->Width = 35;
		// 
		// columnHeader14
		// 
		this->columnHeader14->Text = L"Line";
		this->columnHeader14->Width = 36;
		// 
		// columnHeader15
		// 
		this->columnHeader15->Text = L"Col";
		this->columnHeader15->Width = 36;
		// 
		// columnHeader16
		// 
		this->columnHeader16->Text = L"Type";
		this->columnHeader16->Width = 90;
		// 
		// columnHeader17
		// 
		this->columnHeader17->Text = L"Name";
		this->columnHeader17->Width = 90;
		// 
		// columnHeader18
		// 
		this->columnHeader18->Text = L"Value";
		this->columnHeader18->Width = 65;
		// 
		// toolStrip1
		// 
		this->toolStrip1->BackColor = System::Drawing::SystemColors::Window;
		this->toolStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Hidden;
		this->toolStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(11) {
			this->tbNewFile, this->tbOpen,
				this->tbSave, this->toolStripSeparator3, this->tbRun, this->toolStripSeparator4, this->tbBuild, this->toolStripSeparator2, this->tbDebug,
				this->tbStepOver, this->tbContinue
		});
		this->toolStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
		this->toolStrip1->Location = System::Drawing::Point(0, 24);
		this->toolStrip1->Name = L"toolStrip1";
		this->toolStrip1->Padding = System::Windows::Forms::Padding(10, 0, 1, 0);
		this->toolStrip1->Size = System::Drawing::Size(1480, 25);
		this->toolStrip1->TabIndex = 14;
		this->toolStrip1->Text = L"toolStrip1";
		// 
		// tbNewFile
		// 
		this->tbNewFile->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbNewFile.Image")));
		this->tbNewFile->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbNewFile->Name = L"tbNewFile";
		this->tbNewFile->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbNewFile->Size = System::Drawing::Size(80, 22);
		this->tbNewFile->Text = L"New File";
		this->tbNewFile->ToolTipText = L"New File (Ctrl+N)";
		this->tbNewFile->Click += gcnew System::EventHandler(this, &Main::tmNewFile_Click);
		// 
		// tbOpen
		// 
		this->tbOpen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbOpen.Image")));
		this->tbOpen->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbOpen->Name = L"tbOpen";
		this->tbOpen->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbOpen->Size = System::Drawing::Size(63, 22);
		this->tbOpen->Text = L"Open";
		this->tbOpen->ToolTipText = L"Open (Ctrl+O)";
		this->tbOpen->Click += gcnew System::EventHandler(this, &Main::tmOpen_Click);
		// 
		// tbSave
		// 
		this->tbSave->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbSave.Image")));
		this->tbSave->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbSave->Name = L"tbSave";
		this->tbSave->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbSave->Size = System::Drawing::Size(59, 22);
		this->tbSave->Text = L"Save";
		this->tbSave->ToolTipText = L"Save (Ctrl+S)";
		this->tbSave->Click += gcnew System::EventHandler(this, &Main::tmSave_Click);
		// 
		// toolStripSeparator3
		// 
		this->toolStripSeparator3->Name = L"toolStripSeparator3";
		this->toolStripSeparator3->Size = System::Drawing::Size(6, 25);
		// 
		// tbRun
		// 
		this->tbRun->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbRun.Image")));
		this->tbRun->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbRun->Name = L"tbRun";
		this->tbRun->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbRun->Size = System::Drawing::Size(55, 22);
		this->tbRun->Text = L"Run";
		this->tbRun->ToolTipText = L"Run (F5)";
		this->tbRun->Click += gcnew System::EventHandler(this, &Main::tmRun_Click);
		// 
		// toolStripSeparator4
		// 
		this->toolStripSeparator4->Name = L"toolStripSeparator4";
		this->toolStripSeparator4->Size = System::Drawing::Size(6, 25);
		// 
		// tbBuild
		// 
		this->tbBuild->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbBuild.Image")));
		this->tbBuild->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbBuild->Name = L"tbBuild";
		this->tbBuild->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbBuild->Size = System::Drawing::Size(61, 22);
		this->tbBuild->Text = L"Build";
		this->tbBuild->ToolTipText = L"Build (F6)";
		this->tbBuild->Click += gcnew System::EventHandler(this, &Main::tmBuild_Click);
		// 
		// toolStripSeparator2
		// 
		this->toolStripSeparator2->Name = L"toolStripSeparator2";
		this->toolStripSeparator2->Size = System::Drawing::Size(6, 25);
		// 
		// tbDebug
		// 
		this->tbDebug->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbDebug.Image")));
		this->tbDebug->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbDebug->Name = L"tbDebug";
		this->tbDebug->Size = System::Drawing::Size(63, 22);
		this->tbDebug->Text = L"Debug";
		this->tbDebug->ToolTipText = L"Debug (F9)";
		this->tbDebug->Click += gcnew System::EventHandler(this, &Main::tmDebug_Click);
		// 
		// tbStepOver
		// 
		this->tbStepOver->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbStepOver.Image")));
		this->tbStepOver->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbStepOver->Name = L"tbStepOver";
		this->tbStepOver->Padding = System::Windows::Forms::Padding(7, 0, 0, 0);
		this->tbStepOver->Size = System::Drawing::Size(87, 22);
		this->tbStepOver->Text = L"Step Over";
		this->tbStepOver->ToolTipText = L"Step Over (F10)";
		this->tbStepOver->Click += gcnew System::EventHandler(this, &Main::tmStepOver_Click);
		// 
		// tbContinue
		// 
		this->tbContinue->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tbContinue.Image")));
		this->tbContinue->ImageTransparentColor = System::Drawing::Color::Magenta;
		this->tbContinue->Name = L"tbContinue";
		this->tbContinue->Size = System::Drawing::Size(76, 22);
		this->tbContinue->Text = L"Continue";
		this->tbContinue->ToolTipText = L"Continue (F10)";
		this->tbContinue->Click += gcnew System::EventHandler(this, &Main::tmContinue_Click);
		// 
		// openFileDialog1
		// 
		this->openFileDialog1->FileName = L"openFileDialog1";
		this->openFileDialog1->Filter = L"Text Files|*.txt";
		this->openFileDialog1->Title = L"Select a Text File";
		// 
		// saveFileDialog1
		// 
		this->saveFileDialog1->Filter = L"Text Files|*.txt";
		this->saveFileDialog1->Title = L"Save a Text File";
		// 
		// panel3
		// 
		this->panel3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Right));
		this->panel3->BackColor = System::Drawing::SystemColors::ControlLight;
		this->panel3->Controls->Add(this->lvByteCodes);
		this->panel3->Controls->Add(this->label4);
		this->panel3->Location = System::Drawing::Point(770, 61);
		this->panel3->Name = L"panel3";
		this->panel3->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		this->panel3->Size = System::Drawing::Size(369, 716);
		this->panel3->TabIndex = 10;
		// 
		// lvByteCodes
		// 
		this->lvByteCodes->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->lvByteCodes->BackColor = System::Drawing::SystemColors::Menu;
		this->lvByteCodes->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->lvByteCodes->CheckBoxes = true;
		this->lvByteCodes->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
			this->BP, this->address,
				this->instruction, this->Value, this->name
		});
		this->lvByteCodes->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->lvByteCodes->FullRowSelect = true;
		this->lvByteCodes->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lvByteCodes->HideSelection = false;
		listViewItem1->StateImageIndex = 0;
		this->lvByteCodes->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(1) { listViewItem1 });
		this->lvByteCodes->Location = System::Drawing::Point(1, 26);
		this->lvByteCodes->MultiSelect = false;
		this->lvByteCodes->Name = L"lvByteCodes";
		this->lvByteCodes->Size = System::Drawing::Size(368, 690);
		this->lvByteCodes->StateImageList = this->imageList1;
		this->lvByteCodes->TabIndex = 13;
		this->lvByteCodes->TabStop = false;
		this->lvByteCodes->UseCompatibleStateImageBehavior = false;
		this->lvByteCodes->View = System::Windows::Forms::View::Details;
		this->lvByteCodes->ItemChecked += gcnew System::Windows::Forms::ItemCheckedEventHandler(this, &Main::lvByteCodes_ItemChecked);
		// 
		// BP
		// 
		this->BP->Text = L"BP";
		this->BP->Width = 26;
		// 
		// address
		// 
		this->address->Text = L"Address";
		this->address->Width = 85;
		// 
		// instruction
		// 
		this->instruction->Text = L"OP Code";
		this->instruction->Width = 80;
		// 
		// Value
		// 
		this->Value->Text = L"Value";
		this->Value->Width = 85;
		// 
		// name
		// 
		this->name->Text = L"Name";
		this->name->Width = 75;
		// 
		// imageList1
		// 
		this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
		this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
		this->imageList1->Images->SetKeyName(0, L"BreakpointDisable_16x.png");
		this->imageList1->Images->SetKeyName(1, L"BreakpointEnable_16x.png");
		// 
		// label4
		// 
		this->label4->BackColor = System::Drawing::SystemColors::Window;
		this->label4->Dock = System::Windows::Forms::DockStyle::Top;
		this->label4->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label4->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label4->Location = System::Drawing::Point(1, 0);
		this->label4->Name = L"label4";
		this->label4->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label4->Size = System::Drawing::Size(368, 26);
		this->label4->TabIndex = 12;
		this->label4->Text = L"Byte Code";
		// 
		// panel4
		// 
		this->panel4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
		this->panel4->BackColor = System::Drawing::SystemColors::ControlLight;
		this->panel4->Controls->Add(this->lvOperandStack);
		this->panel4->Controls->Add(this->label5);
		this->panel4->Location = System::Drawing::Point(1320, 61);
		this->panel4->Name = L"panel4";
		this->panel4->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		this->panel4->Size = System::Drawing::Size(148, 184);
		this->panel4->TabIndex = 15;
		// 
		// lvOperandStack
		// 
		this->lvOperandStack->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->lvOperandStack->BackColor = System::Drawing::SystemColors::Menu;
		this->lvOperandStack->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->lvOperandStack->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
			this->columnHeader2,
				this->columnHeader4
		});
		this->lvOperandStack->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->lvOperandStack->FullRowSelect = true;
		this->lvOperandStack->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lvOperandStack->HideSelection = false;
		this->lvOperandStack->Location = System::Drawing::Point(1, 26);
		this->lvOperandStack->Name = L"lvOperandStack";
		this->lvOperandStack->Size = System::Drawing::Size(147, 158);
		this->lvOperandStack->TabIndex = 12;
		this->lvOperandStack->TabStop = false;
		this->lvOperandStack->UseCompatibleStateImageBehavior = false;
		this->lvOperandStack->View = System::Windows::Forms::View::Details;
		this->lvOperandStack->VirtualMode = true;
		this->lvOperandStack->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &Main::lvOperandStack_RetrieveVirtualItem);
		// 
		// columnHeader2
		// 
		this->columnHeader2->Text = L"No";
		this->columnHeader2->Width = 40;
		// 
		// columnHeader4
		// 
		this->columnHeader4->Text = L"Value";
		this->columnHeader4->Width = 90;
		// 
		// label5
		// 
		this->label5->BackColor = System::Drawing::SystemColors::Window;
		this->label5->Dock = System::Windows::Forms::DockStyle::Top;
		this->label5->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label5->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label5->Location = System::Drawing::Point(1, 0);
		this->label5->Name = L"label5";
		this->label5->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label5->Size = System::Drawing::Size(147, 26);
		this->label5->TabIndex = 11;
		this->label5->Text = L"Operand Stack";
		// 
		// panel5
		// 
		this->panel5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Right));
		this->panel5->BackColor = System::Drawing::SystemColors::ControlLight;
		this->panel5->Controls->Add(this->lvDataSegment);
		this->panel5->Controls->Add(this->label2);
		this->panel5->Location = System::Drawing::Point(1157, 61);
		this->panel5->Name = L"panel5";
		this->panel5->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		this->panel5->Size = System::Drawing::Size(148, 716);
		this->panel5->TabIndex = 16;
		// 
		// lvDataSegment
		// 
		this->lvDataSegment->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->lvDataSegment->BackColor = System::Drawing::SystemColors::Menu;
		this->lvDataSegment->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->lvDataSegment->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
			this->columnHeader1,
				this->columnHeader24
		});
		this->lvDataSegment->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->lvDataSegment->FullRowSelect = true;
		this->lvDataSegment->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lvDataSegment->HideSelection = false;
		this->lvDataSegment->Location = System::Drawing::Point(1, 26);
		this->lvDataSegment->MultiSelect = false;
		this->lvDataSegment->Name = L"lvDataSegment";
		this->lvDataSegment->Size = System::Drawing::Size(147, 690);
		this->lvDataSegment->TabIndex = 14;
		this->lvDataSegment->TabStop = false;
		this->lvDataSegment->UseCompatibleStateImageBehavior = false;
		this->lvDataSegment->View = System::Windows::Forms::View::Details;
		this->lvDataSegment->VirtualMode = true;
		this->lvDataSegment->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &Main::lvDataSegment_RetrieveVirtualItem);
		// 
		// columnHeader1
		// 
		this->columnHeader1->Text = L"No";
		this->columnHeader1->Width = 40;
		// 
		// columnHeader24
		// 
		this->columnHeader24->Text = L"Value";
		this->columnHeader24->Width = 90;
		// 
		// label2
		// 
		this->label2->BackColor = System::Drawing::SystemColors::Window;
		this->label2->Dock = System::Windows::Forms::DockStyle::Top;
		this->label2->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label2->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label2->Location = System::Drawing::Point(1, 0);
		this->label2->Name = L"label2";
		this->label2->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label2->Size = System::Drawing::Size(147, 26);
		this->label2->TabIndex = 5;
		this->label2->Text = L"Data Segment";
		// 
		// panel6
		// 
		this->panel6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Right));
		this->panel6->BackColor = System::Drawing::SystemColors::ControlLight;
		this->panel6->Controls->Add(this->lvStackSegment);
		this->panel6->Controls->Add(this->lbStackSegmentInfo);
		this->panel6->Controls->Add(this->label3);
		this->panel6->Location = System::Drawing::Point(1320, 251);
		this->panel6->Name = L"panel6";
		this->panel6->Padding = System::Windows::Forms::Padding(1, 0, 0, 0);
		this->panel6->Size = System::Drawing::Size(148, 526);
		this->panel6->TabIndex = 16;
		// 
		// lvStackSegment
		// 
		this->lvStackSegment->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
			| System::Windows::Forms::AnchorStyles::Left)
			| System::Windows::Forms::AnchorStyles::Right));
		this->lvStackSegment->BackColor = System::Drawing::SystemColors::Menu;
		this->lvStackSegment->BorderStyle = System::Windows::Forms::BorderStyle::None;
		this->lvStackSegment->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
			this->columnHeader3,
				this->columnHeader6
		});
		this->lvStackSegment->Font = (gcnew System::Drawing::Font(L"Consolas", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->lvStackSegment->FullRowSelect = true;
		this->lvStackSegment->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
		this->lvStackSegment->HideSelection = false;
		this->lvStackSegment->Location = System::Drawing::Point(1, 26);
		this->lvStackSegment->MultiSelect = false;
		this->lvStackSegment->Name = L"lvStackSegment";
		this->lvStackSegment->Size = System::Drawing::Size(147, 481);
		this->lvStackSegment->TabIndex = 15;
		this->lvStackSegment->TabStop = false;
		this->lvStackSegment->UseCompatibleStateImageBehavior = false;
		this->lvStackSegment->View = System::Windows::Forms::View::Details;
		this->lvStackSegment->VirtualMode = true;
		this->lvStackSegment->RetrieveVirtualItem += gcnew System::Windows::Forms::RetrieveVirtualItemEventHandler(this, &Main::lvStackSegment_RetrieveVirtualItem);
		// 
		// columnHeader3
		// 
		this->columnHeader3->Text = L"No";
		this->columnHeader3->Width = 40;
		// 
		// columnHeader6
		// 
		this->columnHeader6->Text = L"Value";
		this->columnHeader6->Width = 90;
		// 
		// lbStackSegmentInfo
		// 
		this->lbStackSegmentInfo->BackColor = System::Drawing::SystemColors::Window;
		this->lbStackSegmentInfo->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->lbStackSegmentInfo->Font = (gcnew System::Drawing::Font(L"Cambria", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->lbStackSegmentInfo->ImageAlign = System::Drawing::ContentAlignment::BottomRight;
		this->lbStackSegmentInfo->Location = System::Drawing::Point(1, 509);
		this->lbStackSegmentInfo->Name = L"lbStackSegmentInfo";
		this->lbStackSegmentInfo->Size = System::Drawing::Size(147, 17);
		this->lbStackSegmentInfo->TabIndex = 7;
		this->lbStackSegmentInfo->Text = L"ESP: 0 / EBP : 0";
		this->lbStackSegmentInfo->TextAlign = System::Drawing::ContentAlignment::TopRight;
		// 
		// label3
		// 
		this->label3->BackColor = System::Drawing::SystemColors::Window;
		this->label3->Dock = System::Windows::Forms::DockStyle::Top;
		this->label3->Font = (gcnew System::Drawing::Font(L"Cambria", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->label3->ForeColor = System::Drawing::SystemColors::HotTrack;
		this->label3->Location = System::Drawing::Point(1, 0);
		this->label3->Name = L"label3";
		this->label3->Padding = System::Windows::Forms::Padding(3, 3, 0, 0);
		this->label3->Size = System::Drawing::Size(147, 26);
		this->label3->TabIndex = 6;
		this->label3->Text = L"Stack Segment";
		// 
		// Main
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->BackColor = System::Drawing::SystemColors::Window;
		this->ClientSize = System::Drawing::Size(1480, 789);
		this->Controls->Add(this->splitContainer3);
		this->Controls->Add(this->panel6);
		this->Controls->Add(this->panel5);
		this->Controls->Add(this->panel4);
		this->Controls->Add(this->panel3);
		this->Controls->Add(this->toolStrip1);
		this->Controls->Add(this->tabControl1);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->menuStrip1);
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->MainMenuStrip = this->menuStrip1;
		this->Name = L"Main";
		this->Text = L"YuLang";
		this->menuStrip1->ResumeLayout(false);
		this->menuStrip1->PerformLayout();
		this->splitContainer3->Panel1->ResumeLayout(false);
		this->splitContainer3->Panel1->PerformLayout();
		this->splitContainer3->Panel2->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer3))->EndInit();
		this->splitContainer3->ResumeLayout(false);
		this->panel1->ResumeLayout(false);
		this->panel2->ResumeLayout(false);
		this->panel2->PerformLayout();
		this->tabControl1->ResumeLayout(false);
		this->tabPage4->ResumeLayout(false);
		this->tabPage4->PerformLayout();
		this->tabPage3->ResumeLayout(false);
		this->tabPage3->PerformLayout();
		this->tabPage1->ResumeLayout(false);
		this->tabPage2->ResumeLayout(false);
		this->toolStrip1->ResumeLayout(false);
		this->toolStrip1->PerformLayout();
		this->panel3->ResumeLayout(false);
		this->panel4->ResumeLayout(false);
		this->panel5->ResumeLayout(false);
		this->panel6->ResumeLayout(false);
		this->ResumeLayout(false);
		this->PerformLayout();

	}

#	pragma endregion
	public: static Main^ mainForm;
	private: bool textChanged;
	private: bool isDebug;

	private: System::Boolean ToChar( RichTextBox^ textBox, char* dst ) {
		size_t n = 0;
		pin_ptr<const wchar_t> wch = PtrToStringChars( textBox->Text );
		size_t  bytes = (wcslen(wch) + 1 ) * 2;
		setlocale( LC_ALL, "" );
		return wcstombs_s( &n, dst, bytes, wch, bytes ) == 0;
	}

	private: System::Void tmNewFile_Click(System::Object^  sender, System::EventArgs^  e) {
		tbSourceCode->Text = tbBasicTemplete->Text;
		tbSourceCode->SelectionStart = 14;
		tbSourceCode->SelectionLength = 0;
		textChanged = true;
		HighlightSourceCode( tbSourceCode, gcnew System::EventArgs() );
	}
	private: System::Void tmOpen_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( openFileDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK ) return;
		tbSourceCode->LoadFile( openFileDialog1->FileName, System::Windows::Forms::RichTextBoxStreamType::UnicodePlainText );
	}
	private: System::Void tmSave_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( saveFileDialog1->ShowDialog() != System::Windows::Forms::DialogResult::OK ) return;
		tbSourceCode->SaveFile( saveFileDialog1->FileName, System::Windows::Forms::RichTextBoxStreamType::UnicodePlainText );
		MessageBox::Show( L"Saved.\n" + saveFileDialog1->FileName );
	}

	private: System::Void tmExit_Click(System::Object^  sender, System::EventArgs^  e) {
		Close();
	}

	private: System::Void tmEditCode_Click(System::Object^  sender, System::EventArgs^  e) {
		tbSourceCode->Focus(); 
	}

	private: System::Void lvByteCodes_ItemChecked(System::Object^  sender, System::Windows::Forms::ItemCheckedEventArgs^  e) {
		codes[ e->Item->Index ].breakPoint = (e->Item->Checked);
	}

	private: System::Void ClearInfo() {
		tbOutput->Clear();
		lvTokenList->Items->Clear();
		tvParseTree->Nodes->Clear();
		lvByteCodes->Items->Clear();
		lvDataSegment->VirtualListSize = 0;
		lvOperandStack->VirtualListSize = 0;
		lvStackSegment->VirtualListSize = 0;
	}

	private: System::Void ShowInfo( PCODE code ) {
		lvByteCodes->Items[ code->idx ]->Selected = true;
		lvByteCodes->Items[ code->idx ]->EnsureVisible();
		lvDataSegment->VirtualListSize = DS_SIZE;
		lvDataSegment->Invalidate();
		lvStackSegment->VirtualListSize = ( ESP > SS_SIZE ) ? 0 : ESP;
		lvStackSegment->Invalidate();
		lvOperandStack->VirtualListSize = ( OSP > OS_SIZE ) ? 0 : OSP;
		lvOperandStack->Invalidate();
		lbStackSegmentInfo->Text = "ESP: " + Convert::ToString( (int)ESP ) 
								 + " / EBP: " + Convert::ToString( (int)EBP );
	}

	private: System::Boolean Build() {
		tbSourceCode->SaveFile( "YuLang.txt", RichTextBoxStreamType::PlainText );
		ClearInfo();
		Print( "========== Build started ========== \r\n" );
		
		Print( "> Converting Source Code... \r\n" );
		static char input[65536] = { 0, };
		if ( ToChar( tbSourceCode, input ) == false ) {
			Print( "error: failed to convert source codes \r\n" );
			return false;
		}
		
		Print( "> Generating Code... \r\n" );
		PTOKEN result = YuBuild( input );
		PrintTokenList( lvTokenList, tokens );
		PrintParseTree( tvParseTree, tokens );
		if ( result->err != E_OK ) {
			Print( GetErrorMessage( result ) );
			return false;
		}

		Print( "========== Build succeeded ========== \r\n" );

		return true;
	}

	private: System::Void tmRun_Click(System::Object^  sender, System::EventArgs^  e) {
		isDebug = false;
		if ( Build() == false ) return;
		tbOutput->Clear();

		YuRun();
		Print( "\r\n========== Program Terminated ========== \r\n" );
	}

	private: System::Void tmBuild_Click(System::Object^  sender, System::EventArgs^  e) {
		isDebug = false;
		Build();
	}

	private: System::Void tmDebug_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( Build() == false ) return;
		tbOutput->Clear();

		PrintCodeList( lvByteCodes, codes );
		ShowInfo( codes );
		isDebug = true;
	}

	private: System::Void tmStepOver_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( isDebug == false ) return;
		PCODE result = YuStepOver();
		if ( result == NULL ) result = prevCode;
		if ( result->type == _DONE ) Print( "\r\n========== Program Terminated ========== \r\n" );
		ShowInfo( result );
	}

	private: System::Void tmContinue_Click(System::Object^  sender, System::EventArgs^  e) {
		if ( isDebug == false ) return;
		PCODE result = YuContinue();
		if ( result == NULL ) result = prevCode;
		if ( result->type == _DONE ) Print( "\r\n========== Program Terminated ========== \r\n" );
		ShowInfo( result );
	}

	private: System::Void lvOperandStack_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e) {
		int i = e->ItemIndex;

		String^ val = Convert::ToString( OS[i] );
		if ( OS[i] > (int)codes && OS[i] < (int)(codes + CODES_SIZE) )
			val = "0x" + IntPtr(OS[i]).ToString( "X8" );

		e->Item = gcnew ListViewItem( Convert::ToString(i) );
		e->Item->SubItems->Add( val );
	}

	private: System::Void lvDataSegment_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e) {
		int i = e->ItemIndex;

		String^ val = Convert::ToString( DS[i] );
		if ( DS[i] > (int)codes && DS[i] < (int)(codes + CODES_SIZE) )
			val = "0x" + IntPtr(DS[i]).ToString( "X8" );

		e->Item = gcnew ListViewItem( Convert::ToString(i) );
		e->Item->SubItems->Add( val );
	}

	private: System::Void lvStackSegment_RetrieveVirtualItem(System::Object^  sender, System::Windows::Forms::RetrieveVirtualItemEventArgs^  e) {
		int i = e->ItemIndex;

		String^ val = Convert::ToString( SS[i] );
		if ( SS[i] > (int)codes && SS[i] < (int)(codes + CODES_SIZE) )
			val = "0x" + IntPtr(SS[i]).ToString( "X8" );

		e->Item = gcnew ListViewItem( Convert::ToString(i) );
		e->Item->SubItems->Add( val );
	}
	
	private: System::Void PrintCodeList( ListView^ listView, PCODE code ) {
		listView->BeginUpdate();
		listView->Items->Clear();
		for ( int i = 0; code[i].type != _UNKNOWN; i++ ) {
			String^ addr = "0x" + IntPtr(code + i).ToString( "X8" );
			String^ type = gcnew String( GetTypeName( code[i].type ) );
			String^ val = "";
			String^ name = "";

			switch ( code[i].type ) {
			case _NUM: case _INC_ESP: case _CALL: case _JZ: case _JNZ: case _JMP:
				val = Convert::ToString(code[i].val);
			}
			if ( code[i].val > (int)codes && code[i].val < (int)(codes + CODES_SIZE) )
				val = "0x" + IntPtr(code[i].val).ToString( "X8" );

			switch ( code[i].type ) {
			case _GMOV:	case _MOV:	case _CALL:	case _GVAL:	case _VAL:
			case _DEF_BEGIN:	case _DEF_END:
				name = gcnew String( code[i].str, 0, code[i].len );
			}

			ListViewItem^ item = listView->Items->Add( "" );
			item->SubItems->Add( addr );
			item->SubItems->Add( type );
			item->SubItems->Add( val );
			item->SubItems->Add( name );
			
			switch ( code[i].type ) {
			case _DEF_BEGIN:	case _DEF_END:
				item->BackColor = Color::Coral;				
				break;
			case _WHILE_BEGIN:	case _WHILE_END:	case _CONTINUE:		case _BREAK:
				item->BackColor = Color::YellowGreen;
				break;
			case _IF_BEGIN:		case _ELIF_BEGIN:	case _ELSE_BEGIN:	case _IF_END: 
				item->BackColor = Color::LightSkyBlue;
				break;
			case _ASSIGN_BEGIN:	case _ASSIGN_END:
			case _INDEX_BEGIN:	case _INDEX_END:	case _INDEX_SEP:
			case _CALL_BEGIN:	case _CALL_END:		case _CALL_SEP:
			case _PRINT_BEGIN:	case _PRINT_END:
			case _RETURN_BEGIN:	case _RETURN_END:
				item->BackColor = Color::LightGray;
				break;
			default:
				item->BackColor = listView->BackColor;
				break;
			}
		}
		listView->EndUpdate();
	}

	private: System::Void PrintTokenList( ListView^ listView, PTOKEN token ) {
		listView->BeginUpdate();
		listView->Items->Clear();
		for ( int i = 0; token[i].type != _DONE; i++ ) {
			ListViewItem^ item = listView->Items->Add( Convert::ToString( i ) );
			item->SubItems->Add( Convert::ToString( (int)(token[i].row) ) );
			item->SubItems->Add( Convert::ToString( (int)(token[i].col) ) );
			item->SubItems->Add( gcnew String( GetTypeName( token[i].type ) ) );
			if ( token[i].str != NULL )
				item->SubItems->Add( gcnew String( token[i].str, 0, token[i].len ) );
			item->SubItems->Add( Convert::ToString( (int)token[i].val ) );
			
		}
		listView->EndUpdate();
	}

	private: System::Void PrintParseTree( TreeView^ treeView, PTOKEN token ) {
		TreeNode^ treeNode = gcnew TreeNode( "<ROOT>" );
		AddParseTreeStatements( treeNode, token );
		treeView->BeginUpdate();
		treeView->Nodes->Clear();		
		treeView->Nodes->Add( treeNode );
		treeView->ExpandAll();
		treeView->Nodes[0]->EnsureVisible();
		treeView->EndUpdate();
	}

	private: System::Void AddParseTreeStatements( TreeNode^ treeNode, PTOKEN token ) {
		TreeNode^ childNode;
		for ( PTOKEN temp = token; temp != NULL; temp = temp->next ) {
			childNode = treeNode->Nodes->Add( GetParseTreeNodeName( temp ) );
			AddParseTreeNodes( childNode, temp->params, "[Parameters:" + Convert::ToString( (int)temp->cnt ) + "]" );
			AddParseTreeNodes( childNode, temp->expr, "[Expression]" );

			if ( temp->ref != NULL ) {
				childNode->Text = childNode->Text + " -> " + GetParseTreeNodeName( temp->ref );
			}

			if ( temp->stmts == NULL ) continue;
			AddParseTreeStatements( childNode, temp->stmts );
		}
	}

	private: System::Void AddParseTreeNodes( TreeNode^ treeNode, PTOKEN token, String^ subject ) {
		if ( token == NULL ) return;
		TreeNode^ childNode = treeNode->Nodes->Add( subject );
		for ( ; token != NULL; token = token->next )
			childNode->Nodes->Add( GetParseTreeNodeName( token ) );
	}

	private: System::String^ GetParseTreeNodeName( PTOKEN token ) {
		String^ str = gcnew String( GetTypeName( token->type ) );

		switch ( token->type ) {
		case _DEF:
			str += ":" + gcnew String( token->str, 0, token->len )
				 + " (" + Convert::ToString( (int)(token->frmSize) ) + ")";
			break;

		case _CALL:
			str += ":" + gcnew String( token->str, 0, token->len );
			break;

		case _GAVAR: case _AVAR:
			str += ":" + gcnew String( token->str, 0, token->len )
				+ " (" + Convert::ToString( token->val )
				+ ":" + Convert::ToString( (int)(token->cnt) ) + ")";
			break;
			
		case _GVAR: case _VAR:
		case _GVAL: case _VAL: 
		case _ASSIGN: case _IDEN:
			str += ":" + gcnew String( token->str, 0, token->len )
				+ " (" + Convert::ToString( token->val ) + ")";
			break;

		case _NUM:
			str += " (" + Convert::ToString( token->val ) + ")";
			break;

		case _WHILE:
			str += " (" + Convert::ToString( (int)(token->row) ) + ")";
			break;

		case _INDEX:
			str = "[" + str + ": " + Convert::ToString( token->val ) + "]";
			break;
		}
		return str;
	}

	public: System::Void Print( const char* msg ) {
		tbOutput->AppendText( gcnew String( msg ) );
	}

	public: System::Void ShowMessage( const char* msg ) {
		MessageBox::Show( gcnew String( msg ) );
	}

	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		switch ( ((ComboBox^)sender)->SelectedIndex ) {
		case 0: tbDrill->Text = tbDrill1->Text; break;
		case 1: tbDrill->Text = tbDrill2->Text; break;
		case 2: tbDrill->Text = tbDrill3->Text; break;
		case 3: tbDrill->Text = tbDrill4->Text; break;
		case 4: tbDrill->Text = tbDrill5->Text; break;
		}
	}

	private: System::Void tbSourceCode_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		if ( ((RichTextBox^)sender)->ImeMode != Windows::Forms::ImeMode::Alpha )
			((RichTextBox^)sender)->ImeMode = Windows::Forms::ImeMode::Alpha;
	}

	private: System::Void tbSourceCode_KeyUp(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
		textChanged = true;
	}

	private: System::Void HighlightSourceCode(System::Object^  sender, System::EventArgs^  e) {
		if ( tbSourceCode->SelectionLength > 0 ) return;
		if ( textChanged == false ) return;
		textChanged = false;

		bool focused = tbSourceCode->Focused;
		if ( focused ) label7->Focus();

		int ss = tbSourceCode->SelectionStart;
		int sl = tbSourceCode->SelectionLength;

		static char input[65536] = { 0, };
		if ( ToChar( tbSourceCode, input ) == false ) return;
		
		static TOKEN tokens[1000] = { _UNKNOWN, };
		YuTokenize( input, tokens );

		for ( int i = 0; tokens[i].type != _DONE; i++ ) {
			switch ( tokens[i].type ) {
			case _VAR:		case _ARR:
			case _DEF:		case _RETURN:
			case _WHILE:	case _BREAK:	case _CONTINUE:
			case _IF: 		case _ELIF:		case _ELSE:
				tbSourceCode->Select( tokens[i].offset, tokens[i].len );
				tbSourceCode->SelectionColor = Color::DeepSkyBlue;
				break;

			case _AND:		case _OR:
			case _CE:		case _CNE:
			case _CBE:		case _CAE:
			case _LPAREN:	case _RPAREN:
			case _LCURLY:	case _RCURLY:
			case _ADD:		case _SUB:
			case _MUL:		case _DIV:
			case _MOD:		case _ASSIGN:
			case _CB:		case _CA:
			case _COMMA:
				tbSourceCode->Select( tokens[i].offset, tokens[i].len );
				tbSourceCode->SelectionColor = Color::YellowGreen;
				break;

			case _COMMENT:
				tbSourceCode->Select( tokens[i].offset, tokens[i].len );
				tbSourceCode->SelectionColor = Color::Green;
				break;

			case _NUM:
				tbSourceCode->Select( tokens[i].offset, tokens[i].len );
				tbSourceCode->SelectionColor = Color::Coral;
				break;

			default:
				tbSourceCode->Select( tokens[i].offset, tokens[i].len );
				tbSourceCode->SelectionColor = Color::FloralWhite;
			}
		}

		tbSourceCode->SelectionStart = ss;
		tbSourceCode->SelectionLength = 0;
		tbSourceCode->SelectionColor = Color::FloralWhite;
		if ( focused ) tbSourceCode->Focus();
	}
private: System::Void cbSample_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
		String^ str;
		switch ( ((ComboBox^)sender)->SelectedIndex ) {
		case 0: str = tbSampleWhile->Text; break;
		case 1: str = tbSampleIf->Text; break;
		case 2: str = tbSampleDef->Text; break;
		case 3: str = tbSampleArray->Text; break;
		case 4: str = tbSampleFactorial->Text; break;
		case 5: str = tbSampleSort->Text; break;
		case 6: str = tbSampleOverflow->Text; break;
		case 7: str = tbSampleMemoryAccess->Text; break;
		case 8: str = tbSampleDevideBy0->Text; break;
		}
		tbSample->Text = str->Replace( "\t", "    " );
}

private: System::Void btnRunSample_Click(System::Object^  sender, System::EventArgs^  e) {
	tbSourceCode->Text = tbSample->Text->Replace( "    ", "\t" );
	textChanged = true;
	tmRun_Click( tmRun, e );
}
};
}