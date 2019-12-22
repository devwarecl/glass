
#pragma once

#ifndef __wcl_filedialog_hpp__
#define __wcl_filedialog_hpp__

#include <string>
#include <algorithm>
#include <Windows.h>

namespace wcl {

	class FileDialog {
	public:

		/**
		 * @brief 
		 */
		FileDialog(const std::wstring &title=L"", const std::wstring &filter=L"");

		bool UserCancel() const;

		std::wstring GetFileName() const;

		void ShowOpen();

		void ShowSave();

		void SetTitle(const std::wstring &title);

		void SetFilter(const std::wstring &filter);

	private:
		/*
		template<typename Function>
		void Show(Function function) {
			OPENFILENAME ofn = m_GetDialogConfig();

			m_userCancel = !function(&ofn);

			if (!m_userCancel) {
				m_fileName = ofn.lpstrFile;
			}
		}
		*/

		OPENFILENAME GetDialogConfig() const;

	private:
		std::wstring m_title;
		std::wstring m_filter;

		std::wstring m_fileName;
		bool m_userCancel = true;

		mutable wchar_t m_fileNameBuffer[2048];
	};


	inline FileDialog::FileDialog(const std::wstring &title, const std::wstring &filter) {
		this->SetTitle(title);
		this->SetFilter(filter);
	}

	inline bool FileDialog::UserCancel() const {
		return m_userCancel;
	}

	inline std::wstring FileDialog::GetFileName() const {
		return m_fileName;
	}

	inline void FileDialog::ShowOpen() {
		OPENFILENAME ofn = this->GetDialogConfig();

		m_userCancel = !::GetOpenFileName(&ofn);

		if (!m_userCancel) {
			m_fileName = ofn.lpstrFile;
		}
	}

	inline void FileDialog::ShowSave() {
		OPENFILENAME ofn = this->GetDialogConfig();

		m_userCancel = !::GetSaveFileName(&ofn);

		if (!m_userCancel) {
			m_fileName = ofn.lpstrFile;
		}
	}

	inline void FileDialog::SetTitle(const std::wstring &title) {
		m_title = title;
	}

	inline void FileDialog::SetFilter(const std::wstring &filter) {
		m_filter = filter;

		std::transform(m_filter.begin(), m_filter.end(), m_filter.begin(), [](wchar_t ch) {
			if (ch == L'|') {
				return L'\0';
			} else {
				return ch;
			}
		});
	}

	inline OPENFILENAME FileDialog::GetDialogConfig() const {
		std::memset(m_fileNameBuffer, 0, sizeof(m_fileNameBuffer));

		OPENFILENAME ofn = {};
		ofn.lStructSize = sizeof(ofn);
		
		ofn.lpstrTitle = m_title.c_str();
		
		ofn.lpstrFilter = m_filter.c_str();
		ofn.nFilterIndex = 1;

		ofn.lpstrFile = m_fileNameBuffer;
		ofn.nMaxFile = sizeof(m_fileNameBuffer);
		ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;

		return ofn;
	}
}

#endif // __wcl_filedialog_hpp__
