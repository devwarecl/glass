
#pragma once

#ifndef __wcl_ex_tabbedpanel_hpp__
#define __wcl_ex_tabbedpanel_hpp__

#include <list>
#include <wcl/Static.hpp>
#include <wcl/Sizer.hpp>
#include <wcl/TabControl.hpp>

namespace wcl { namespace ex {
    
    class TabbedPanel : public Static {
    public:
        class Tab {
        public:
            explicit Tab(Window *window, TabControl *tabControl) {
                m_window = window;
                m_tabControl = tabControl;
            }

            void SetText(const std::wstring &text) {
                const int index = this->GetIndex();

                wcl::TabControlItem item = {};

                item.mask = TCIF_TEXT;
                item.pszText = const_cast<wchar_t*>(text.c_str());

                m_tabControl->SetItem(index, item);
            }

            std::wstring GetText() const {
                const int index = this->GetIndex();

                wcl::TabControlItem item = {};
                item.mask = TCIF_TEXT;

                m_tabControl->GetItem(index, &item);

                return item.pszText;
            }

            Window* GetWindow() const {
                return m_window;
            }

            int GetIndex() const {
                return m_tabControl->GetChildIndex(m_window);;
            }

        private:
            Window* m_window = nullptr;
            TabControl *m_tabControl = nullptr;
        };

    public:
        virtual void OnCreate() override;
        virtual void OnNotify(const int id, const NMHDR* nmhdr) override;
        virtual void OnSize(const int w, const int h) override;
        
        Tab* AppendTab(const std::wstring &label, wcl::WindowPtr childWindow);

        void RemoveTab(Tab* tab);

        bool TryRemoveTab(Tab* tab);

        Tab* GetTab(const int i);
        const Tab* GetTab(const int i) const;

        const int GetTabCount() const;

        Tab* GetCurrentTab() const;

        void SetCurrentTab(const Tab* tab);

        Tab* GetTab(const wcl::Window *window);

        const Tab* GetTab(const wcl::Window *window) const;

    private:
        void resizeChild(const int index);
    
        void displayChild(const int index);
        
    private:
        TabControl m_tabControl;
        Sizer m_sizer;

        std::vector<std::unique_ptr<Tab>> m_tabs;
    };
    
    inline void TabbedPanel::OnCreate() {
        m_tabControl.Create(L"", WS_CHILD|WS_VISIBLE, 0, 0, 20, 20, this->GetHandle());
        
        m_sizer.Add(&m_tabControl, SizerStyle::Expand);
    }
    
    inline void TabbedPanel::OnNotify(const int id, const NMHDR* nmhdr) {
        if (nmhdr->code == TCN_SELCHANGE) {
            const int index = m_tabControl.GetCurSel();
            
            if (index != -1) {
                this->resizeChild(index);
                this->displayChild(index);
            }
        }
    }
    
    inline void TabbedPanel::OnSize(int w, int h) {
        const int index = m_tabControl.GetCurSel();

        if (index >= 0) {
            this->resizeChild(index);
            this->displayChild(index);
        }
        
        m_sizer.OnSize(w, h);
    }
    
    inline TabbedPanel::Tab* TabbedPanel::GetCurrentTab() const {
        return m_tabs[m_tabControl.GetCurSel()].get();
    }

    inline void TabbedPanel::SetCurrentTab(const TabbedPanel::Tab* tab) {
        m_tabControl.SetCurSel(tab->GetIndex());
    }

    inline TabbedPanel::Tab* TabbedPanel::AppendTab(const std::wstring &label, wcl::WindowPtr childWindow) {
        auto tab = std::make_unique<TabbedPanel::Tab>(childWindow.get(), &m_tabControl);
        auto result = tab.get();

        const int index = m_tabControl.GetChildCount();
        
        // insert the item into de tab control
        m_tabControl.InsertItem(index, wcl::TabControlItem::Text(label));

        // let the tab control adopt the child
        m_tabControl.AddChild(std::move(childWindow));
        
        // automatically set the new tab as the current one
        m_tabControl.SetCurSel(index);
        
        // display the tab
        this->resizeChild(index);
        this->displayChild(index);

        // store the tab wrapper...
        m_tabs.push_back(std::move(tab));

        // finish the implementation
        return result;
    }
    
    inline void TabbedPanel::RemoveTab(Tab* tab) {

    }

    inline bool TabbedPanel::TryRemoveTab(Tab* tab) {
        
    }

    inline TabbedPanel::Tab* TabbedPanel::GetTab(const int i) {
        return m_tabs[i].get();
    }

    inline const TabbedPanel::Tab* TabbedPanel::GetTab(const int i) const {
        return m_tabs[i].get();
    }

    inline const int TabbedPanel::GetTabCount() const {
        return m_tabs.size();
    }

    inline void TabbedPanel::resizeChild(const int index) {
        Rect clientRect = m_tabControl.GetClientRect();
                
        m_tabControl.AdjustRect(FALSE, &clientRect);
        m_tabControl.GetChild(index)->SetPos(NULL, clientRect);
    }

    inline void TabbedPanel::displayChild(const int index) {
        for (int i=0; i<m_tabControl.GetChildCount(); i++) {
            int nCmdShow = SW_HIDE;
            
            if (i == index) {
                nCmdShow = SW_NORMAL;
            }
            
            m_tabControl.GetChild(i)->Show(nCmdShow);
        }
    }

    inline TabbedPanel::Tab* TabbedPanel::GetTab(const wcl::Window *window) {
        TabbedPanel::Tab* tab = nullptr;

        for (int i=0; i<this->GetTabCount(); i++) {
            if (this->GetTab(i)->GetWindow() == window ) {
                tab = this->GetTab(i);
                break;
            }
        }

        return tab;
    }
    
    inline const TabbedPanel::Tab* TabbedPanel::GetTab(const wcl::Window *window) const {
        const TabbedPanel::Tab* tab = nullptr;

        for (int i=0; i<this->GetTabCount(); i++) {
            if (this->GetTab(i)->GetWindow() == window ) {
                tab = this->GetTab(i);
                break;
            }
        }

        return tab;
    }
}}

#endif
