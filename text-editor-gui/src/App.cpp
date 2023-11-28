#include "App.h"
#include "Mechanics.h"
#include <functional> // trying out stuff too with this header
#include <iostream> // I don't want to invoke a debugger when I can stdout

#define GREY ImVec4(43/255.0f, 43/255.0f, 43/255.0f, 1.0f)

void center_next_window(){
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

}
void show_modal_for_opening(bool * can_open){
	ImGui::OpenPopup("Open file");
	center_next_window();
	ImGui::PushStyleColor(ImGuiCol_PopupBg, GREY);
	ImGui::PushStyleColor(ImGuiCol_Border, GREY);
	ImGui::PushStyleColor(ImGuiCol_CheckMark, GREY);
	if(ImGui::BeginPopupModal("Open file", can_open, ImGuiWindowFlags_AlwaysAutoResize)){

		ImGui::Text("Want to open file?");
		if(ImGui::Button("Close"))
			ImGui::CloseCurrentPopup();
			*can_open = false;
		ImGui::EndPopup();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

}

void show_modal_for_saving(bool * open){
	ImGui::OpenPopup("Save file");
	center_next_window();
	ImGui::PushStyleColor(ImGuiCol_PopupBg, GREY);
	ImGui::PushStyleColor(ImGuiCol_Button, GREY);
	ImGui::PushStyleColor(ImGuiCol_Border, GREY);

	if(ImGui::BeginPopupModal("Save file", open, ImGuiWindowFlags_AlwaysAutoResize)){
		ImGui::Text("Save file?");
		if(ImGui::Button("Exit"))
			ImGui::CloseCurrentPopup();
			*open = false;
		
		ImGui::EndPopup();
	}
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();
}
void show_modal_for_creation(bool * is_open){
					static char input[256];
					ImGui::OpenPopup("Create filename");
					ImVec2 center = ImGui::GetMainViewport()->GetCenter();
					ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
          ImGui::PushStyleColor(ImGuiCol_PopupBg,	GREY);
					ImGui::PushStyleColor(ImGuiCol_Button, GREY);
					ImGui::PushStyleColor(ImGuiCol_Border, GREY);
				if(ImGui::BeginPopupModal("Create filename", is_open, ImGuiWindowFlags_AlwaysAutoResize)){
					ImGui::InputText("##input", input, IM_ARRAYSIZE(input));
					if(ImGui::Button("Exit")){
						ImGui::CloseCurrentPopup();
						*is_open = false;
					}
					ImGui::SameLine();
					if(ImGui::Button("Submit")){
						Mechanics::Create_File(input);
						ImGui::CloseCurrentPopup();
						*is_open = false;
						
					}
					ImGui::Separator();
					ImGui::EndPopup();
				}
          ImGui::PopStyleColor();
					ImGui::PopStyleColor();
					ImGui::PopStyleColor();	

}


void Myapp::renderUI(){
	ImGuiWindowFlags flags = 0;
	flags |= ImGuiWindowFlags_NoResize;
	flags |= ImGuiWindowFlags_MenuBar;
	flags |= ImGuiWindowFlags_NoTitleBar;
	ImGui::Begin("Hello", NULL, flags);

	ImGuiStyle& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_WindowBg] = GREY;
	style.Colors[ImGuiCol_Text] = ImVec4(0.90f, 0.90f, 0.90f, 1.0f);
	style.Colors[ImGuiCol_MenuBarBg] = GREY;
	style.Colors[ImGuiCol_ScrollbarBg] = GREY;
	style.Colors[ImGuiCol_Border] = ImVec4(0/255.0f, 0/255.0f, 0/255.0f, 1.0f);

	ImGui::SetWindowSize(ImVec2(700, 600));

	[[maybe_unused]]static bool show_creation_modal = false;
	[[maybe_unused]]static bool show_opening_modal = false;
	[[maybe_unused]]static bool show_saving_modal = false;

	static bool exit = false;

	//Bunch of conditions to see if I can make modals
	if(exit)
		std::exit(0);

	if(show_creation_modal){
		show_modal_for_creation(&show_creation_modal);
	}

	if(show_opening_modal){
		show_modal_for_opening(&show_opening_modal);
	}
	if(show_saving_modal){
		show_modal_for_saving(&show_saving_modal);
	}
	//
	if(ImGui::BeginMenuBar()){
		if(ImGui::BeginMenu("File")){
      ImGui::MenuItem("New" ,"CTRL+N", &show_creation_modal, true);
			ImGui::MenuItem("Open", "CTRL+O", &show_opening_modal, true);
			ImGui::MenuItem("Save", "CTRL+S", &show_saving_modal, true);
			ImGui::MenuItem("Save as", "CTRL+SHIFT+S");
			ImGui::Separator();
			ImGui::MenuItem("Page Setup");
			ImGui::MenuItem("Print", "CTRL+P");
			ImGui::Separator();
			ImGui::MenuItem("Exit", NULL, &exit, true);
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Edit")){
			ImGui::MenuItem("Undo", "CTRL+Z");
			ImGui::MenuItem("Repeat", "CTRL+SHIFT+Z");
			ImGui::Separator();
			ImGui::MenuItem("Cut", "CTRL+Z");
			ImGui::MenuItem("Copy", "CTRL+C");
			ImGui::MenuItem("Paste", "CTRL+V");
			ImGui::MenuItem("Delete", "Del");
			ImGui::Separator();
			ImGui::MenuItem("Select all", "CTRL+a");
			ImGui::MenuItem("Time/Date", "F5");
			ImGui::Separator();
			ImGui::MenuItem("Word wrap");
			ImGui::MenuItem("Set Font");
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Search")){
			ImGui::MenuItem("Find", "CTRL+F");
			ImGui::MenuItem("Find Next", "F3");
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("Help")){
			ImGui::MenuItem("Help Topics");
			ImGui::Separator();
			ImGui::MenuItem("About Notepad");
			ImGui::EndMenu();	
		}
		ImGui::EndMenuBar();
	}

	static char text[1024*16];
	//ImGui::DragValue("Value: ", value);
	ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(43/255.0f, 43/255.0f, 43/255.0f, 1.0f));
	ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight()*35));	
	ImGui::PopStyleColor();
	[[maybe_unused]]static bool show_app = true;

	ImGui::End();

	//ImGui::ShowDemoWindow();

}
