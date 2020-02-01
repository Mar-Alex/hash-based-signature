#pragma once

#pragma managed(push,off)
#include "UserInterface.h"
#include "cryptopp/sha.h"
#include "HashAlgorithmGenerator.h"
#include <map>
#pragma managed(pop)

#include <msclr/marshal_cppstd.h>

namespace DiplomaUI {

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for MainForm
/// </summary>
public ref class MainForm : public System::Windows::Forms::Form
{
	std::map<int, CryptoPP::HashTransformation*> *hashAlgorithms;
	//System::String ^publicKeyFilepath;
	System::String ^privateKeyFilepath;
	System::String ^currentPassword;
	WOTS_MerkleTreePrivateKey **privateKey;
	//CryptoPP::Integer *publicKey;
	CryptoPP::HashTransformation **hasher;

	bool isFileChosen;
	bool isSignChosen;
	bool isKeyChosen;

private: System::Windows::Forms::RadioButton^  keyModeRadioButton2;
private: System::Windows::Forms::RadioButton^  keyModeRadioButton1;
private: System::Windows::Forms::CheckBox^  saveExtKeyCheckBox;
private: System::Windows::Forms::TextBox^  genKeyExtPrivateKeyTextBox;


private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Label^  label14;
private: System::Windows::Forms::Button^  closeButton;
private: System::Windows::Forms::CheckBox^  reloadKeyCheckBox;

	

public:
	MainForm(void)
	{
		InitializeComponent();
		hashAlgorithms = HashAlgorithmGenerator::getHashes();
		//publicKeyFilepath = gcnew System::String("");
		privateKeyFilepath = gcnew System::String("");
		hasher = new CryptoPP::HashTransformation*;
		privateKey = new WOTS_MerkleTreePrivateKey*;
		*privateKey = nullptr;
		isFileChosen = false;
		isSignChosen = false;
		isKeyChosen = false;
		pictureBox1->Image = Image::FromFile("Graphics/image.png");
		this->Icon = gcnew Drawing::Icon("Graphics/4.ico");
	}
	

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~MainForm()
	{
		if (components)
		{
			delete components;
		}
	}

protected:
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::Label^  createSignChoosePrivKeyLabel;

private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
private: System::Windows::Forms::Button^  createSignChoosePrivKeyButton;
private: System::Windows::Forms::Button^  createSignButton;
private: System::Windows::Forms::Button^  verifySignatureButton;


private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Button^  genKeyButton;

private: System::Windows::Forms::Label^  label6;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label8;
private: System::Windows::Forms::ComboBox^  hashComboBox;
private: System::Windows::Forms::ComboBox^  numberComboBox;
private: System::Windows::Forms::ComboBox^  wintComboBox;



private: System::Windows::Forms::Label^  label9;
private: System::Windows::Forms::TextBox^  genKeyPasswordTextBox;

private: System::Windows::Forms::TextBox^  genKeyPrivateKeyTextBox;



private: System::Windows::Forms::Label^  label10;
private: System::Windows::Forms::TextBox^  genKeyPublicKeyTextBox;


private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label4;
private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Button^  createSignChooseFileButton;
private: System::Windows::Forms::Label^  createSignChooseFileLabel;
private: System::Windows::Forms::Button^  verifySignChooseFileButton;
private: System::Windows::Forms::Label^  verifySignChooseFileLabel;

private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Button^  verifySignChoosePublicKeyButton;
private: System::Windows::Forms::Label^  verifySignChoosePublicKeyLabel;

private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::TextBox^  createSignNameTextBox;

private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Button^  verifySignChooseSignButton;
private: System::Windows::Forms::Label^  verifySignChooseSignLabel;


private: System::Windows::Forms::Label^  label21;
private: System::Windows::Forms::Panel^  generateKeyPanel;
private: System::Windows::Forms::Button^  genKeyBackButton;


private: System::Windows::Forms::Panel^  createSignaturePanel;
private: System::Windows::Forms::Button^  createSignBackButton;


private: System::Windows::Forms::Panel^  verifySignaturePanel;
private: System::Windows::Forms::Button^  verifySignBackButton;



private: System::Windows::Forms::Panel^  menuPanel;
private: System::Windows::Forms::Button^  menuVerifySignButton;


private: System::Windows::Forms::Button^  menuCreateSignButton;

private: System::Windows::Forms::Button^  menuGenKeyButton;
private: System::Windows::Forms::PictureBox^  pictureBox1;
private: System::Windows::Forms::TextBox^  createSignPasswordTextBox;

private: System::Windows::Forms::Label^  label3;

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->createSignChoosePrivKeyLabel = (gcnew System::Windows::Forms::Label());
		this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		this->createSignChoosePrivKeyButton = (gcnew System::Windows::Forms::Button());
		this->createSignButton = (gcnew System::Windows::Forms::Button());
		this->verifySignatureButton = (gcnew System::Windows::Forms::Button());
		this->label5 = (gcnew System::Windows::Forms::Label());
		this->genKeyButton = (gcnew System::Windows::Forms::Button());
		this->label6 = (gcnew System::Windows::Forms::Label());
		this->label7 = (gcnew System::Windows::Forms::Label());
		this->label8 = (gcnew System::Windows::Forms::Label());
		this->hashComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->numberComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->wintComboBox = (gcnew System::Windows::Forms::ComboBox());
		this->label9 = (gcnew System::Windows::Forms::Label());
		this->genKeyPasswordTextBox = (gcnew System::Windows::Forms::TextBox());
		this->genKeyPrivateKeyTextBox = (gcnew System::Windows::Forms::TextBox());
		this->label10 = (gcnew System::Windows::Forms::Label());
		this->genKeyPublicKeyTextBox = (gcnew System::Windows::Forms::TextBox());
		this->label11 = (gcnew System::Windows::Forms::Label());
		this->label4 = (gcnew System::Windows::Forms::Label());
		this->label12 = (gcnew System::Windows::Forms::Label());
		this->createSignChooseFileButton = (gcnew System::Windows::Forms::Button());
		this->createSignChooseFileLabel = (gcnew System::Windows::Forms::Label());
		this->verifySignChooseFileButton = (gcnew System::Windows::Forms::Button());
		this->verifySignChooseFileLabel = (gcnew System::Windows::Forms::Label());
		this->label15 = (gcnew System::Windows::Forms::Label());
		this->label16 = (gcnew System::Windows::Forms::Label());
		this->verifySignChoosePublicKeyButton = (gcnew System::Windows::Forms::Button());
		this->verifySignChoosePublicKeyLabel = (gcnew System::Windows::Forms::Label());
		this->label18 = (gcnew System::Windows::Forms::Label());
		this->createSignNameTextBox = (gcnew System::Windows::Forms::TextBox());
		this->label19 = (gcnew System::Windows::Forms::Label());
		this->verifySignChooseSignButton = (gcnew System::Windows::Forms::Button());
		this->verifySignChooseSignLabel = (gcnew System::Windows::Forms::Label());
		this->label21 = (gcnew System::Windows::Forms::Label());
		this->generateKeyPanel = (gcnew System::Windows::Forms::Panel());
		this->label14 = (gcnew System::Windows::Forms::Label());
		this->saveExtKeyCheckBox = (gcnew System::Windows::Forms::CheckBox());
		this->genKeyBackButton = (gcnew System::Windows::Forms::Button());
		this->genKeyExtPrivateKeyTextBox = (gcnew System::Windows::Forms::TextBox());
		this->label13 = (gcnew System::Windows::Forms::Label());
		this->createSignaturePanel = (gcnew System::Windows::Forms::Panel());
		this->keyModeRadioButton2 = (gcnew System::Windows::Forms::RadioButton());
		this->keyModeRadioButton1 = (gcnew System::Windows::Forms::RadioButton());
		this->reloadKeyCheckBox = (gcnew System::Windows::Forms::CheckBox());
		this->createSignPasswordTextBox = (gcnew System::Windows::Forms::TextBox());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->createSignBackButton = (gcnew System::Windows::Forms::Button());
		this->verifySignaturePanel = (gcnew System::Windows::Forms::Panel());
		this->verifySignBackButton = (gcnew System::Windows::Forms::Button());
		this->menuPanel = (gcnew System::Windows::Forms::Panel());
		this->closeButton = (gcnew System::Windows::Forms::Button());
		this->menuVerifySignButton = (gcnew System::Windows::Forms::Button());
		this->menuCreateSignButton = (gcnew System::Windows::Forms::Button());
		this->menuGenKeyButton = (gcnew System::Windows::Forms::Button());
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->generateKeyPanel->SuspendLayout();
		this->createSignaturePanel->SuspendLayout();
		this->verifySignaturePanel->SuspendLayout();
		this->menuPanel->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		this->SuspendLayout();
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label1->Location = System::Drawing::Point(250, 455);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(335, 17);
		this->label1->TabIndex = 1;
		this->label1->Text = L"Марухненко Александр. БИКС-15-2. ХНУРЭ. 2019";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label2->Location = System::Drawing::Point(27, 239);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(224, 17);
		this->label2->TabIndex = 2;
		this->label2->Text = L"Выберите подписываемый файл";
		// 
		// createSignChoosePrivKeyLabel
		// 
		this->createSignChoosePrivKeyLabel->AutoSize = true;
		this->createSignChoosePrivKeyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignChoosePrivKeyLabel->Location = System::Drawing::Point(30, 129);
		this->createSignChoosePrivKeyLabel->Name = L"createSignChoosePrivKeyLabel";
		this->createSignChoosePrivKeyLabel->Size = System::Drawing::Size(103, 15);
		this->createSignChoosePrivKeyLabel->TabIndex = 3;
		this->createSignChoosePrivKeyLabel->Text = L"Файл не выбран";
		// 
		// openFileDialog1
		// 
		this->openFileDialog1->FileName = L"openFileDialog1";
		// 
		// createSignChoosePrivKeyButton
		// 
		this->createSignChoosePrivKeyButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignChoosePrivKeyButton->Location = System::Drawing::Point(312, 93);
		this->createSignChoosePrivKeyButton->Name = L"createSignChoosePrivKeyButton";
		this->createSignChoosePrivKeyButton->Size = System::Drawing::Size(85, 25);
		this->createSignChoosePrivKeyButton->TabIndex = 4;
		this->createSignChoosePrivKeyButton->Text = L"Выбрать";
		this->createSignChoosePrivKeyButton->UseVisualStyleBackColor = true;
		this->createSignChoosePrivKeyButton->Click += gcnew System::EventHandler(this, &MainForm::createSignChoosePrivKeyButton_Click);
		// 
		// createSignButton
		// 
		this->createSignButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->createSignButton->Location = System::Drawing::Point(130, 371);
		this->createSignButton->Name = L"createSignButton";
		this->createSignButton->Size = System::Drawing::Size(151, 43);
		this->createSignButton->TabIndex = 5;
		this->createSignButton->Text = L"Создать подпись";
		this->createSignButton->UseVisualStyleBackColor = true;
		this->createSignButton->Click += gcnew System::EventHandler(this, &MainForm::createSignButton_Click);
		// 
		// verifySignatureButton
		// 
		this->verifySignatureButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignatureButton->Location = System::Drawing::Point(130, 300);
		this->verifySignatureButton->Name = L"verifySignatureButton";
		this->verifySignatureButton->Size = System::Drawing::Size(138, 42);
		this->verifySignatureButton->TabIndex = 6;
		this->verifySignatureButton->Text = L"Проверить подпись";
		this->verifySignatureButton->UseVisualStyleBackColor = true;
		this->verifySignatureButton->Click += gcnew System::EventHandler(this, &MainForm::verifySignatureButton_Click);
		// 
		// label5
		// 
		this->label5->AutoSize = true;
		this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label5->Location = System::Drawing::Point(135, 13);
		this->label5->Name = L"label5";
		this->label5->Size = System::Drawing::Size(168, 22);
		this->label5->TabIndex = 8;
		this->label5->Text = L"Генерация ключей";
		this->label5->TextAlign = System::Drawing::ContentAlignment::TopCenter;
		// 
		// genKeyButton
		// 
		this->genKeyButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->genKeyButton->Location = System::Drawing::Point(130, 385);
		this->genKeyButton->Name = L"genKeyButton";
		this->genKeyButton->Size = System::Drawing::Size(177, 33);
		this->genKeyButton->TabIndex = 9;
		this->genKeyButton->Text = L"Сгенерировать";
		this->genKeyButton->UseVisualStyleBackColor = true;
		this->genKeyButton->Click += gcnew System::EventHandler(this, &MainForm::genKeyButton_Click);
		// 
		// label6
		// 
		this->label6->AutoSize = true;
		this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label6->Location = System::Drawing::Point(30, 74);
		this->label6->Name = L"label6";
		this->label6->Size = System::Drawing::Size(97, 17);
		this->label6->TabIndex = 10;
		this->label6->Text = L"Хэш-функция";
		// 
		// label7
		// 
		this->label7->AutoSize = true;
		this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label7->Location = System::Drawing::Point(144, 74);
		this->label7->Name = L"label7";
		this->label7->Size = System::Drawing::Size(86, 34);
		this->label7->TabIndex = 11;
		this->label7->Text = L"Количество\r\nподписей";
		// 
		// label8
		// 
		this->label8->AutoSize = true;
		this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label8->Location = System::Drawing::Point(264, 74);
		this->label8->Name = L"label8";
		this->label8->Size = System::Drawing::Size(88, 34);
		this->label8->TabIndex = 12;
		this->label8->Text = L"Параметр \r\nВинтерница";
		// 
		// hashComboBox
		// 
		this->hashComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->hashComboBox->FormattingEnabled = true;
		this->hashComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(13) {
			L"SHA1", L"SHA256", L"SHA512", L"SHA3(256)",
				L"SHA3(512)", L"BLAKE2b", L"SHAKE256", L"Tiger", L"RIPEMD128", L"RIPEMD256", L"WHIRLPOOL", L"SM3", L"MD5"
		});
		this->hashComboBox->Location = System::Drawing::Point(30, 115);
		this->hashComboBox->Name = L"hashComboBox";
		this->hashComboBox->Size = System::Drawing::Size(85, 21);
		this->hashComboBox->TabIndex = 13;
		// 
		// numberComboBox
		// 
		this->numberComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->numberComboBox->FormattingEnabled = true;
		this->numberComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(6) { L"64", L"128", L"256", L"512", L"1024", L"2048" });
		this->numberComboBox->Location = System::Drawing::Point(145, 115);
		this->numberComboBox->Name = L"numberComboBox";
		this->numberComboBox->Size = System::Drawing::Size(85, 21);
		this->numberComboBox->TabIndex = 14;
		// 
		// wintComboBox
		// 
		this->wintComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->wintComboBox->FormattingEnabled = true;
		this->wintComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
			L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9",
				L"10"
		});
		this->wintComboBox->Location = System::Drawing::Point(265, 115);
		this->wintComboBox->Name = L"wintComboBox";
		this->wintComboBox->Size = System::Drawing::Size(85, 21);
		this->wintComboBox->TabIndex = 15;
		// 
		// label9
		// 
		this->label9->AutoSize = true;
		this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label9->Location = System::Drawing::Point(30, 154);
		this->label9->Name = L"label9";
		this->label9->Size = System::Drawing::Size(209, 17);
		this->label9->TabIndex = 16;
		this->label9->Text = L"Пароль для приватного ключа";
		// 
		// genKeyPasswordTextBox
		// 
		this->genKeyPasswordTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->genKeyPasswordTextBox->Location = System::Drawing::Point(33, 186);
		this->genKeyPasswordTextBox->Name = L"genKeyPasswordTextBox";
		this->genKeyPasswordTextBox->Size = System::Drawing::Size(181, 22);
		this->genKeyPasswordTextBox->TabIndex = 17;
		this->genKeyPasswordTextBox->UseSystemPasswordChar = true;
		// 
		// genKeyPrivateKeyTextBox
		// 
		this->genKeyPrivateKeyTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->genKeyPrivateKeyTextBox->Location = System::Drawing::Point(30, 265);
		this->genKeyPrivateKeyTextBox->Name = L"genKeyPrivateKeyTextBox";
		this->genKeyPrivateKeyTextBox->Size = System::Drawing::Size(181, 22);
		this->genKeyPrivateKeyTextBox->TabIndex = 19;
		this->genKeyPrivateKeyTextBox->Text = L"PrivateKey";
		// 
		// label10
		// 
		this->label10->AutoSize = true;
		this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label10->Location = System::Drawing::Point(30, 230);
		this->label10->Name = L"label10";
		this->label10->Size = System::Drawing::Size(206, 17);
		this->label10->TabIndex = 18;
		this->label10->Text = L"Имя файла приватного ключа";
		// 
		// genKeyPublicKeyTextBox
		// 
		this->genKeyPublicKeyTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->genKeyPublicKeyTextBox->Location = System::Drawing::Point(30, 343);
		this->genKeyPublicKeyTextBox->Name = L"genKeyPublicKeyTextBox";
		this->genKeyPublicKeyTextBox->Size = System::Drawing::Size(181, 22);
		this->genKeyPublicKeyTextBox->TabIndex = 21;
		this->genKeyPublicKeyTextBox->Text = L"PublicKey";
		// 
		// label11
		// 
		this->label11->AutoSize = true;
		this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label11->Location = System::Drawing::Point(30, 305);
		this->label11->Name = L"label11";
		this->label11->Size = System::Drawing::Size(199, 17);
		this->label11->TabIndex = 20;
		this->label11->Text = L"Имя файла открытого ключа";
		// 
		// label4
		// 
		this->label4->AutoSize = true;
		this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label4->Location = System::Drawing::Point(134, 9);
		this->label4->Name = L"label4";
		this->label4->Size = System::Drawing::Size(168, 22);
		this->label4->TabIndex = 22;
		this->label4->Text = L"Создание подписи";
		// 
		// label12
		// 
		this->label12->AutoSize = true;
		this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label12->Location = System::Drawing::Point(30, 99);
		this->label12->Name = L"label12";
		this->label12->Size = System::Drawing::Size(237, 17);
		this->label12->TabIndex = 23;
		this->label12->Text = L"Выберите файл приватного ключа";
		// 
		// createSignChooseFileButton
		// 
		this->createSignChooseFileButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignChooseFileButton->Location = System::Drawing::Point(312, 233);
		this->createSignChooseFileButton->Name = L"createSignChooseFileButton";
		this->createSignChooseFileButton->Size = System::Drawing::Size(85, 25);
		this->createSignChooseFileButton->TabIndex = 25;
		this->createSignChooseFileButton->Text = L"Выбрать";
		this->createSignChooseFileButton->UseVisualStyleBackColor = true;
		this->createSignChooseFileButton->Click += gcnew System::EventHandler(this, &MainForm::createSignChooseFileButton_Click);
		// 
		// createSignChooseFileLabel
		// 
		this->createSignChooseFileLabel->AutoSize = true;
		this->createSignChooseFileLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignChooseFileLabel->Location = System::Drawing::Point(28, 265);
		this->createSignChooseFileLabel->Name = L"createSignChooseFileLabel";
		this->createSignChooseFileLabel->Size = System::Drawing::Size(103, 15);
		this->createSignChooseFileLabel->TabIndex = 24;
		this->createSignChooseFileLabel->Text = L"Файл не выбран";
		// 
		// verifySignChooseFileButton
		// 
		this->verifySignChooseFileButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChooseFileButton->Location = System::Drawing::Point(299, 125);
		this->verifySignChooseFileButton->Name = L"verifySignChooseFileButton";
		this->verifySignChooseFileButton->Size = System::Drawing::Size(85, 25);
		this->verifySignChooseFileButton->TabIndex = 30;
		this->verifySignChooseFileButton->Text = L"Выбрать";
		this->verifySignChooseFileButton->UseVisualStyleBackColor = true;
		this->verifySignChooseFileButton->Click += gcnew System::EventHandler(this, &MainForm::verifySignChooseFileButton_Click);
		// 
		// verifySignChooseFileLabel
		// 
		this->verifySignChooseFileLabel->AutoSize = true;
		this->verifySignChooseFileLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChooseFileLabel->Location = System::Drawing::Point(28, 161);
		this->verifySignChooseFileLabel->Name = L"verifySignChooseFileLabel";
		this->verifySignChooseFileLabel->Size = System::Drawing::Size(103, 15);
		this->verifySignChooseFileLabel->TabIndex = 30;
		this->verifySignChooseFileLabel->Text = L"Файл не выбран";
		// 
		// label15
		// 
		this->label15->AutoSize = true;
		this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label15->Location = System::Drawing::Point(30, 53);
		this->label15->Name = L"label15";
		this->label15->Size = System::Drawing::Size(230, 17);
		this->label15->TabIndex = 31;
		this->label15->Text = L"Выберите файл открытого ключа";
		// 
		// label16
		// 
		this->label16->AutoSize = true;
		this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label16->Location = System::Drawing::Point(135, 13);
		this->label16->Name = L"label16";
		this->label16->Size = System::Drawing::Size(167, 22);
		this->label16->TabIndex = 30;
		this->label16->Text = L"Проверка подписи";
		// 
		// verifySignChoosePublicKeyButton
		// 
		this->verifySignChoosePublicKeyButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChoosePublicKeyButton->Location = System::Drawing::Point(299, 50);
		this->verifySignChoosePublicKeyButton->Name = L"verifySignChoosePublicKeyButton";
		this->verifySignChoosePublicKeyButton->Size = System::Drawing::Size(85, 25);
		this->verifySignChoosePublicKeyButton->TabIndex = 28;
		this->verifySignChoosePublicKeyButton->Text = L"Выбрать";
		this->verifySignChoosePublicKeyButton->UseVisualStyleBackColor = true;
		this->verifySignChoosePublicKeyButton->Click += gcnew System::EventHandler(this, &MainForm::verifySignChoosePublicKeyButton_Click);
		// 
		// verifySignChoosePublicKeyLabel
		// 
		this->verifySignChoosePublicKeyLabel->AutoSize = true;
		this->verifySignChoosePublicKeyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChoosePublicKeyLabel->Location = System::Drawing::Point(30, 84);
		this->verifySignChoosePublicKeyLabel->Name = L"verifySignChoosePublicKeyLabel";
		this->verifySignChoosePublicKeyLabel->Size = System::Drawing::Size(103, 15);
		this->verifySignChoosePublicKeyLabel->TabIndex = 27;
		this->verifySignChoosePublicKeyLabel->Text = L"Файл не выбран";
		// 
		// label18
		// 
		this->label18->AutoSize = true;
		this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label18->Location = System::Drawing::Point(28, 130);
		this->label18->Name = L"label18";
		this->label18->Size = System::Drawing::Size(207, 17);
		this->label18->TabIndex = 26;
		this->label18->Text = L"Выберите проверяемый файл";
		// 
		// createSignNameTextBox
		// 
		this->createSignNameTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignNameTextBox->Location = System::Drawing::Point(33, 334);
		this->createSignNameTextBox->Name = L"createSignNameTextBox";
		this->createSignNameTextBox->Size = System::Drawing::Size(181, 22);
		this->createSignNameTextBox->TabIndex = 35;
		// 
		// label19
		// 
		this->label19->AutoSize = true;
		this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label19->Location = System::Drawing::Point(30, 300);
		this->label19->Name = L"label19";
		this->label19->Size = System::Drawing::Size(141, 17);
		this->label19->TabIndex = 34;
		this->label19->Text = L"Имя файла подписи";
		// 
		// verifySignChooseSignButton
		// 
		this->verifySignChooseSignButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChooseSignButton->Location = System::Drawing::Point(299, 203);
		this->verifySignChooseSignButton->Name = L"verifySignChooseSignButton";
		this->verifySignChooseSignButton->Size = System::Drawing::Size(85, 25);
		this->verifySignChooseSignButton->TabIndex = 38;
		this->verifySignChooseSignButton->Text = L"Выбрать";
		this->verifySignChooseSignButton->UseVisualStyleBackColor = true;
		this->verifySignChooseSignButton->Click += gcnew System::EventHandler(this, &MainForm::verifySignChooseSignButton_Click);
		// 
		// verifySignChooseSignLabel
		// 
		this->verifySignChooseSignLabel->AutoSize = true;
		this->verifySignChooseSignLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignChooseSignLabel->Location = System::Drawing::Point(30, 237);
		this->verifySignChooseSignLabel->Name = L"verifySignChooseSignLabel";
		this->verifySignChooseSignLabel->Size = System::Drawing::Size(103, 15);
		this->verifySignChooseSignLabel->TabIndex = 37;
		this->verifySignChooseSignLabel->Text = L"Файл не выбран";
		// 
		// label21
		// 
		this->label21->AutoSize = true;
		this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label21->Location = System::Drawing::Point(30, 206);
		this->label21->Name = L"label21";
		this->label21->Size = System::Drawing::Size(172, 17);
		this->label21->TabIndex = 36;
		this->label21->Text = L"Выберите файл подписи";
		// 
		// generateKeyPanel
		// 
		this->generateKeyPanel->Controls->Add(this->label14);
		this->generateKeyPanel->Controls->Add(this->saveExtKeyCheckBox);
		this->generateKeyPanel->Controls->Add(this->genKeyBackButton);
		this->generateKeyPanel->Controls->Add(this->label5);
		this->generateKeyPanel->Controls->Add(this->label8);
		this->generateKeyPanel->Controls->Add(this->label7);
		this->generateKeyPanel->Controls->Add(this->label6);
		this->generateKeyPanel->Controls->Add(this->wintComboBox);
		this->generateKeyPanel->Controls->Add(this->numberComboBox);
		this->generateKeyPanel->Controls->Add(this->hashComboBox);
		this->generateKeyPanel->Controls->Add(this->genKeyPublicKeyTextBox);
		this->generateKeyPanel->Controls->Add(this->label11);
		this->generateKeyPanel->Controls->Add(this->genKeyPrivateKeyTextBox);
		this->generateKeyPanel->Controls->Add(this->label10);
		this->generateKeyPanel->Controls->Add(this->genKeyPasswordTextBox);
		this->generateKeyPanel->Controls->Add(this->label9);
		this->generateKeyPanel->Controls->Add(this->genKeyButton);
		this->generateKeyPanel->Controls->Add(this->genKeyExtPrivateKeyTextBox);
		this->generateKeyPanel->Controls->Add(this->label13);
		this->generateKeyPanel->Location = System::Drawing::Point(0, 0);
		this->generateKeyPanel->Name = L"generateKeyPanel";
		this->generateKeyPanel->Size = System::Drawing::Size(572, 480);
		this->generateKeyPanel->TabIndex = 39;
		this->generateKeyPanel->Visible = false;
		// 
		// label14
		// 
		this->label14->AutoSize = true;
		this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label14->Location = System::Drawing::Point(126, 47);
		this->label14->Name = L"label14";
		this->label14->Size = System::Drawing::Size(84, 17);
		this->label14->TabIndex = 24;
		this->label14->Text = L"Параметры";
		// 
		// saveExtKeyCheckBox
		// 
		this->saveExtKeyCheckBox->AutoSize = true;
		this->saveExtKeyCheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->saveExtKeyCheckBox->Location = System::Drawing::Point(263, 187);
		this->saveExtKeyCheckBox->Name = L"saveExtKeyCheckBox";
		this->saveExtKeyCheckBox->Size = System::Drawing::Size(229, 21);
		this->saveExtKeyCheckBox->TabIndex = 22;
		this->saveExtKeyCheckBox->Text = L"Сохранить расширенный ключ";
		this->saveExtKeyCheckBox->UseVisualStyleBackColor = true;
		// 
		// genKeyBackButton
		// 
		this->genKeyBackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->genKeyBackButton->Location = System::Drawing::Point(30, 435);
		this->genKeyBackButton->Name = L"genKeyBackButton";
		this->genKeyBackButton->Size = System::Drawing::Size(75, 23);
		this->genKeyBackButton->TabIndex = 0;
		this->genKeyBackButton->Text = L"Назад";
		this->genKeyBackButton->UseVisualStyleBackColor = true;
		this->genKeyBackButton->Click += gcnew System::EventHandler(this, &MainForm::genKeyBackButton_Click);
		// 
		// genKeyExtPrivateKeyTextBox
		// 
		this->genKeyExtPrivateKeyTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->genKeyExtPrivateKeyTextBox->Location = System::Drawing::Point(260, 265);
		this->genKeyExtPrivateKeyTextBox->Name = L"genKeyExtPrivateKeyTextBox";
		this->genKeyExtPrivateKeyTextBox->Size = System::Drawing::Size(181, 22);
		this->genKeyExtPrivateKeyTextBox->TabIndex = 23;
		this->genKeyExtPrivateKeyTextBox->Text = L"PrivateKeyExt";
		// 
		// label13
		// 
		this->label13->AutoSize = true;
		this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label13->Location = System::Drawing::Point(260, 230);
		this->label13->Name = L"label13";
		this->label13->Size = System::Drawing::Size(305, 17);
		this->label13->TabIndex = 22;
		this->label13->Text = L"Имя файла расширенного приватного ключа";
		// 
		// createSignaturePanel
		// 
		this->createSignaturePanel->Controls->Add(this->keyModeRadioButton2);
		this->createSignaturePanel->Controls->Add(this->keyModeRadioButton1);
		this->createSignaturePanel->Controls->Add(this->reloadKeyCheckBox);
		this->createSignaturePanel->Controls->Add(this->createSignPasswordTextBox);
		this->createSignaturePanel->Controls->Add(this->label3);
		this->createSignaturePanel->Controls->Add(this->createSignBackButton);
		this->createSignaturePanel->Controls->Add(this->createSignNameTextBox);
		this->createSignaturePanel->Controls->Add(this->label19);
		this->createSignaturePanel->Controls->Add(this->createSignChooseFileButton);
		this->createSignaturePanel->Controls->Add(this->createSignChooseFileLabel);
		this->createSignaturePanel->Controls->Add(this->label12);
		this->createSignaturePanel->Controls->Add(this->label4);
		this->createSignaturePanel->Controls->Add(this->createSignButton);
		this->createSignaturePanel->Controls->Add(this->createSignChoosePrivKeyButton);
		this->createSignaturePanel->Controls->Add(this->createSignChoosePrivKeyLabel);
		this->createSignaturePanel->Controls->Add(this->label2);
		this->createSignaturePanel->Location = System::Drawing::Point(0, 0);
		this->createSignaturePanel->Name = L"createSignaturePanel";
		this->createSignaturePanel->Size = System::Drawing::Size(400, 480);
		this->createSignaturePanel->TabIndex = 40;
		this->createSignaturePanel->Visible = false;
		// 
		// keyModeRadioButton2
		// 
		this->keyModeRadioButton2->AutoSize = true;
		this->keyModeRadioButton2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->keyModeRadioButton2->Location = System::Drawing::Point(33, 69);
		this->keyModeRadioButton2->Name = L"keyModeRadioButton2";
		this->keyModeRadioButton2->Size = System::Drawing::Size(150, 21);
		this->keyModeRadioButton2->TabIndex = 41;
		this->keyModeRadioButton2->TabStop = true;
		this->keyModeRadioButton2->Text = L"Развёрнутый ключ";
		this->keyModeRadioButton2->UseVisualStyleBackColor = true;
		// 
		// keyModeRadioButton1
		// 
		this->keyModeRadioButton1->AutoSize = true;
		this->keyModeRadioButton1->Checked = true;
		this->keyModeRadioButton1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->keyModeRadioButton1->Location = System::Drawing::Point(33, 43);
		this->keyModeRadioButton1->Name = L"keyModeRadioButton1";
		this->keyModeRadioButton1->Size = System::Drawing::Size(114, 21);
		this->keyModeRadioButton1->TabIndex = 40;
		this->keyModeRadioButton1->TabStop = true;
		this->keyModeRadioButton1->Text = L"Сжатый ключ";
		this->keyModeRadioButton1->UseVisualStyleBackColor = true;
		// 
		// reloadKeyCheckBox
		// 
		this->reloadKeyCheckBox->AutoSize = true;
		this->reloadKeyCheckBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->reloadKeyCheckBox->Location = System::Drawing::Point(204, 43);
		this->reloadKeyCheckBox->Name = L"reloadKeyCheckBox";
		this->reloadKeyCheckBox->Size = System::Drawing::Size(162, 21);
		this->reloadKeyCheckBox->TabIndex = 39;
		this->reloadKeyCheckBox->Text = L"Перезагрузить ключ";
		this->reloadKeyCheckBox->UseVisualStyleBackColor = true;
		// 
		// createSignPasswordTextBox
		// 
		this->createSignPasswordTextBox->Location = System::Drawing::Point(33, 188);
		this->createSignPasswordTextBox->Name = L"createSignPasswordTextBox";
		this->createSignPasswordTextBox->Size = System::Drawing::Size(184, 20);
		this->createSignPasswordTextBox->TabIndex = 38;
		this->createSignPasswordTextBox->UseSystemPasswordChar = true;
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->label3->Location = System::Drawing::Point(30, 161);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(238, 17);
		this->label3->TabIndex = 37;
		this->label3->Text = L"Введите пароль приватного ключа";
		// 
		// createSignBackButton
		// 
		this->createSignBackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->createSignBackButton->Location = System::Drawing::Point(43, 430);
		this->createSignBackButton->Name = L"createSignBackButton";
		this->createSignBackButton->Size = System::Drawing::Size(75, 23);
		this->createSignBackButton->TabIndex = 36;
		this->createSignBackButton->Text = L"Назад";
		this->createSignBackButton->UseVisualStyleBackColor = true;
		this->createSignBackButton->Click += gcnew System::EventHandler(this, &MainForm::createSignBackButton_Click);
		// 
		// verifySignaturePanel
		// 
		this->verifySignaturePanel->Controls->Add(this->verifySignBackButton);
		this->verifySignaturePanel->Controls->Add(this->verifySignChooseSignButton);
		this->verifySignaturePanel->Controls->Add(this->verifySignChooseSignLabel);
		this->verifySignaturePanel->Controls->Add(this->label21);
		this->verifySignaturePanel->Controls->Add(this->verifySignChooseFileButton);
		this->verifySignaturePanel->Controls->Add(this->verifySignChooseFileLabel);
		this->verifySignaturePanel->Controls->Add(this->label15);
		this->verifySignaturePanel->Controls->Add(this->label16);
		this->verifySignaturePanel->Controls->Add(this->verifySignChoosePublicKeyButton);
		this->verifySignaturePanel->Controls->Add(this->verifySignChoosePublicKeyLabel);
		this->verifySignaturePanel->Controls->Add(this->label18);
		this->verifySignaturePanel->Controls->Add(this->verifySignatureButton);
		this->verifySignaturePanel->Location = System::Drawing::Point(0, 0);
		this->verifySignaturePanel->Name = L"verifySignaturePanel";
		this->verifySignaturePanel->Size = System::Drawing::Size(400, 480);
		this->verifySignaturePanel->TabIndex = 41;
		this->verifySignaturePanel->Visible = false;
		// 
		// verifySignBackButton
		// 
		this->verifySignBackButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->verifySignBackButton->Location = System::Drawing::Point(40, 434);
		this->verifySignBackButton->Name = L"verifySignBackButton";
		this->verifySignBackButton->Size = System::Drawing::Size(75, 23);
		this->verifySignBackButton->TabIndex = 39;
		this->verifySignBackButton->Text = L"Назад";
		this->verifySignBackButton->UseVisualStyleBackColor = true;
		this->verifySignBackButton->Click += gcnew System::EventHandler(this, &MainForm::verifySignBackButton_Click);
		// 
		// menuPanel
		// 
		this->menuPanel->Controls->Add(this->closeButton);
		this->menuPanel->Controls->Add(this->menuVerifySignButton);
		this->menuPanel->Controls->Add(this->menuCreateSignButton);
		this->menuPanel->Controls->Add(this->menuGenKeyButton);
		this->menuPanel->Location = System::Drawing::Point(0, 0);
		this->menuPanel->Name = L"menuPanel";
		this->menuPanel->Size = System::Drawing::Size(400, 480);
		this->menuPanel->TabIndex = 42;
		// 
		// closeButton
		// 
		this->closeButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->closeButton->Location = System::Drawing::Point(204, 326);
		this->closeButton->Name = L"closeButton";
		this->closeButton->Size = System::Drawing::Size(180, 40);
		this->closeButton->TabIndex = 3;
		this->closeButton->Text = L"Выход";
		this->closeButton->UseVisualStyleBackColor = true;
		this->closeButton->Click += gcnew System::EventHandler(this, &MainForm::closeButton_Click);
		// 
		// menuVerifySignButton
		// 
		this->menuVerifySignButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->menuVerifySignButton->Location = System::Drawing::Point(204, 264);
		this->menuVerifySignButton->Name = L"menuVerifySignButton";
		this->menuVerifySignButton->Size = System::Drawing::Size(180, 40);
		this->menuVerifySignButton->TabIndex = 2;
		this->menuVerifySignButton->Text = L"Проверка подписи";
		this->menuVerifySignButton->UseVisualStyleBackColor = true;
		this->menuVerifySignButton->Click += gcnew System::EventHandler(this, &MainForm::button14_Click);
		// 
		// menuCreateSignButton
		// 
		this->menuCreateSignButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular,
			System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
		this->menuCreateSignButton->Location = System::Drawing::Point(204, 201);
		this->menuCreateSignButton->Name = L"menuCreateSignButton";
		this->menuCreateSignButton->Size = System::Drawing::Size(180, 40);
		this->menuCreateSignButton->TabIndex = 1;
		this->menuCreateSignButton->Text = L"Создание подписи";
		this->menuCreateSignButton->UseVisualStyleBackColor = true;
		this->menuCreateSignButton->Click += gcnew System::EventHandler(this, &MainForm::button13_Click);
		// 
		// menuGenKeyButton
		// 
		this->menuGenKeyButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(204)));
		this->menuGenKeyButton->Location = System::Drawing::Point(204, 136);
		this->menuGenKeyButton->Name = L"menuGenKeyButton";
		this->menuGenKeyButton->Size = System::Drawing::Size(180, 40);
		this->menuGenKeyButton->TabIndex = 0;
		this->menuGenKeyButton->Text = L"Генерация ключей";
		this->menuGenKeyButton->UseVisualStyleBackColor = true;
		this->menuGenKeyButton->Click += gcnew System::EventHandler(this, &MainForm::button12_Click);
		// 
		// pictureBox1
		// 
		this->pictureBox1->Location = System::Drawing::Point(430, 14);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(109, 104);
		this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
		this->pictureBox1->TabIndex = 43;
		this->pictureBox1->TabStop = false;
		// 
		// MainForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(594, 479);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->pictureBox1);
		this->Controls->Add(this->menuPanel);
		this->Controls->Add(this->verifySignaturePanel);
		this->Controls->Add(this->generateKeyPanel);
		this->Controls->Add(this->createSignaturePanel);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		this->MaximizeBox = false;
		this->Name = L"MainForm";
		this->Text = L"HashSignature";
		this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
		this->generateKeyPanel->ResumeLayout(false);
		this->generateKeyPanel->PerformLayout();
		this->createSignaturePanel->ResumeLayout(false);
		this->createSignaturePanel->PerformLayout();
		this->verifySignaturePanel->ResumeLayout(false);
		this->verifySignaturePanel->PerformLayout();
		this->menuPanel->ResumeLayout(false);
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion
private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void button12_Click(System::Object^  sender, System::EventArgs^  e) {
	menuPanel->Visible = false;
	generateKeyPanel->Visible = true;
}
private: System::Void button13_Click(System::Object^  sender, System::EventArgs^  e) {
	menuPanel->Visible = false;
	createSignaturePanel->Visible = true;
}
private: System::Void button14_Click(System::Object^  sender, System::EventArgs^  e) {
	menuPanel->Visible = false;
	verifySignaturePanel->Visible = true;
}


private: System::Void genKeyBackButton_Click(System::Object^  sender, System::EventArgs^  e) {
	generateKeyPanel->Visible = false;
	menuPanel->Visible = true;
	*hasher = nullptr;
	genKeyPasswordTextBox->Text = L"";
	genKeyPrivateKeyTextBox->Text = L"PrivateKey";
	genKeyExtPrivateKeyTextBox->Text = L"PrivateKeyExt";
	genKeyPublicKeyTextBox->Text = L"PublicKey";
	hashComboBox->SelectedIndex = -1;
	numberComboBox->SelectedIndex = -1;
	wintComboBox->SelectedIndex = -1;
	saveExtKeyCheckBox->Checked = false;
}
private: System::Void verifySignBackButton_Click(System::Object^  sender, System::EventArgs^  e) {
	verifySignaturePanel->Visible = false;
	verifySignChoosePublicKeyLabel->Text = L"Файл не выбран";
	verifySignChooseFileLabel->Text = L"Файл не выбран";
	verifySignChooseSignLabel->Text = L"Файл не выбран";
	menuPanel->Visible = true;
	*hasher = nullptr;
	isFileChosen = false;
	isSignChosen = false;
	isKeyChosen = false;
}
private: System::Void createSignBackButton_Click(System::Object^  sender, System::EventArgs^  e) {
	createSignaturePanel->Visible = false;
	createSignChooseFileLabel->Text = L"Файл не выбран";
	createSignChoosePrivKeyLabel->Text = L"Файл не выбран";
	menuPanel->Visible = true;
	*hasher = nullptr;
	isFileChosen = false;
	isKeyChosen = false;
	createSignPasswordTextBox->Text = L"";
	createSignNameTextBox->Text = L"";
	reloadKeyCheckBox->Checked = false;
	keyModeRadioButton1->Checked = true;
}

	
private: System::Void createSignChoosePrivKeyButton_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Reset();
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		createSignChoosePrivKeyLabel->Text = openFileDialog1->FileName;
		isKeyChosen = true;
	}
}
private: System::Void createSignChooseFileButton_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Reset();
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		createSignChooseFileLabel->Text = openFileDialog1->FileName;
		isFileChosen = true;
		if (createSignNameTextBox->Text->Length == 0)
			createSignNameTextBox->Text = createSignChooseFileLabel->Text + L"_signature";
	}
}

private: System::Void verifySignChoosePublicKeyButton_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Reset();
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		verifySignChoosePublicKeyLabel->Text = openFileDialog1->FileName;
		isKeyChosen = true;
	}
}
private: System::Void verifySignChooseFileButton_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Reset();
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		verifySignChooseFileLabel->Text = openFileDialog1->FileName;
		isFileChosen = true;
	}
}
private: System::Void verifySignChooseSignButton_Click(System::Object^  sender, System::EventArgs^  e) {
	openFileDialog1->Reset();
	if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		verifySignChooseSignLabel->Text = openFileDialog1->FileName;
		isSignChosen = true;
	}
}

private: System::Void genKeyButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (hashComboBox->SelectedIndex == -1 || wintComboBox->SelectedIndex == -1 \
		|| numberComboBox->SelectedIndex == -1) {
		MessageBox::Show(this, L"Установите параметры алгоритма", L"Ошибка");
		return;		
	}
	if (genKeyPasswordTextBox->Text->Length == 0 || genKeyPrivateKeyTextBox->Text->Length == 0 \
		|| genKeyPublicKeyTextBox->Text->Length == 0 || \
		(saveExtKeyCheckBox->Checked && genKeyExtPrivateKeyTextBox->Text->Length == 0)) {
		MessageBox::Show(this, L"Заполните все поля", L"Ошибка");
		return;
	}

	*hasher = hashAlgorithms->find(hashComboBox->SelectedIndex)->second;
	std::string *password = new std::string;
	*password = msclr::interop::marshal_as<std::string>(genKeyPasswordTextBox->Text);
	std::string *publicKeyFilename = new std::string;
	*publicKeyFilename = msclr::interop::marshal_as<std::string>(genKeyPublicKeyTextBox->Text);
	if (UserInterface::checkFilename(*publicKeyFilename, false)) {
		MessageBox::Show(this, L"Некорректное имя открытого ключа");
		return;
	}
	std::string *privateKeyFilename = new std::string;
	*privateKeyFilename = msclr::interop::marshal_as<std::string>(genKeyPrivateKeyTextBox->Text);
	if (UserInterface::checkFilename(*privateKeyFilename, false)) {
		MessageBox::Show(this, L"Некорректное имя секретного ключа");
		return;
	}
	std::string *extPrivateKeyFilename = new std::string;
	*extPrivateKeyFilename = msclr::interop::marshal_as<std::string>(genKeyExtPrivateKeyTextBox->Text);
	if (saveExtKeyCheckBox->Checked && UserInterface::checkFilename(*extPrivateKeyFilename, false)) {
		MessageBox::Show(this, L"Подписываемый файл не существует");
		return;
	}
	int treeSize = System::Convert::ToInt32(numberComboBox->Text);
	int w = System::Convert::ToInt32(wintComboBox->Text);
	int generationResult = UserInterface::generateKeyPair(*hasher, &(*password)[0], (*password).length(),treeSize, w, *publicKeyFilename, *privateKeyFilename, *extPrivateKeyFilename, hashAlgorithms, saveExtKeyCheckBox->Checked);
	delete password;
	delete publicKeyFilename;
	delete privateKeyFilename;
	delete extPrivateKeyFilename;
	if(generationResult)
		MessageBox::Show(this, L"Ошибка при записи в файл");
	else
		MessageBox::Show(this, L"Ключ успешно сгенерирован");
}

private: System::Void verifySignatureButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!isFileChosen) {
		MessageBox::Show(this, L"Выберите файл");
		return;
	}
	if (!isSignChosen) {
		MessageBox::Show(this, L"Выберите файл подписи");
		return;
	}
	if (!isKeyChosen) {
		MessageBox::Show(this, L"Выберите открытый ключ");
		return;
	}

	std::string *filename = new std::string;
	*filename = msclr::interop::marshal_as<std::string>(verifySignChooseFileLabel->Text);
	if (UserInterface::checkFilename(*filename, true)) {
		MessageBox::Show(this, L"Подписываемый файл не существует");
		return;
	}
	std::string *signatureFilename = new std::string;
	*signatureFilename = msclr::interop::marshal_as<std::string>(verifySignChooseSignLabel->Text);
	if (UserInterface::checkFilename(*signatureFilename, true)) {
		MessageBox::Show(this, L"Файл подписи не существует");
		return;
	}
	std::string *publicKeyFilename = new std::string;
	*publicKeyFilename = msclr::interop::marshal_as<std::string>(verifySignChoosePublicKeyLabel->Text);
	if (UserInterface::checkFilename(*publicKeyFilename, true)) {
		MessageBox::Show(this, L"Файл приватного ключа не существует");
		return;
	}
	int result = UserInterface::verifySignature(*filename, *signatureFilename, *publicKeyFilename, hashAlgorithms);
	switch (result){
	case 0:
		MessageBox::Show(this, L"Подпись корректна");
		break;
	default:
		MessageBox::Show(this, L"Подпись некорректна");
		break;
	}
	delete filename;
	delete publicKeyFilename;
	delete signatureFilename;
}

private: System::Void createSignButton_Click(System::Object^  sender, System::EventArgs^  e) {
	if (!isFileChosen) {
		MessageBox::Show(this, L"Выберите файл");
		return;
	}
	if (!isKeyChosen) {
		MessageBox::Show(this, L"Выберите открытый ключ");
		return;
	}
	if (System::String::Compare(createSignChoosePrivKeyLabel->Text, privateKeyFilepath)\
		|| System::String::Compare(createSignPasswordTextBox->Text, currentPassword)) {
		if (*privateKey)
			delete *privateKey;
		*hasher = nullptr;
		privateKeyFilepath = createSignChoosePrivKeyLabel->Text;
	}

	std::string *filename = new std::string;
	*filename = msclr::interop::marshal_as<std::string>(createSignChooseFileLabel->Text);
	if (UserInterface::checkFilename(*filename, true)) {
		MessageBox::Show(this, L"Подписываемый файл не существует");
		return;
	}
	std::string *signatureFilename = new std::string;
	*signatureFilename = msclr::interop::marshal_as<std::string>(createSignNameTextBox->Text);
	if (UserInterface::checkFilename(*signatureFilename, false)) {
		MessageBox::Show(this, L"Имя файла подписи некорректно");
		return;
	}
	std::string *privateKeyFilename = new std::string;
	*privateKeyFilename = msclr::interop::marshal_as<std::string>(createSignChoosePrivKeyLabel->Text);
	if (UserInterface::checkFilename(*privateKeyFilename, true)) {
		MessageBox::Show(this, L"Файл приватного ключа не существует");
		return;
	}
	std::string *password = new std::string;
	*password = msclr::interop::marshal_as<std::string>(createSignPasswordTextBox->Text);
	
	if (*hasher == nullptr || reloadKeyCheckBox->Checked) {
		int readResult;
		if(keyModeRadioButton1->Checked)
			readResult = UserInterface::readPrivateKey(*hasher, *privateKey, &(*password)[0], (*password).length(), *privateKeyFilename, hashAlgorithms);
		else
			readResult = UserInterface::readPrivateKeyExt(*hasher, *privateKey, &(*password)[0], (*password).length(), *privateKeyFilename, hashAlgorithms);
		if (readResult) {
			MessageBox::Show(this, L"Пароль неверный либо ключ повреждён");
			return;
		}
	}
	if ((*privateKey)->index >= (*privateKey)->N) {
		MessageBox::Show(this, L"Исчерпан лимит подписей для данного ключа");
		return;
	}
	int result = UserInterface::createSignature(*filename, *signatureFilename, *privateKeyFilename, *password, *hasher, \
		*privateKey, hashAlgorithms, keyModeRadioButton1->Checked);
	switch (result) {
	case 0:
		UserInterface::writePrivateKey(*hasher, **privateKey, (char*)&(*password)[0], password->length(), *privateKeyFilename, hashAlgorithms);
		MessageBox::Show(this, L"Подпись усешно создана");
		break;
	default:
		MessageBox::Show(this, L"Ошибка при создании подписи");
		break;
	}

	delete filename;
	delete privateKeyFilename;
	delete signatureFilename;
	delete password;
}
private: System::Void closeButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->Close();
}
};
}
