#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "j1Scene.h"

j1Gui::j1Gui() : j1Module()
{
	name = "gui";
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.data());
	focusedUi = nullptr;
	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	return true;
}

bool j1Gui::Update(float dt) {
	if (MouseClick() && UiUnderMouse() != nullptr && UiUnderMouse()->interactuable) {
		focusedUi = UiUnderMouse();
		if (focusedUi->Module != nullptr) {
			focusedUi->Module->ui_callback(focusedUi);
		}
	}
	else if (MouseClick() && UiUnderMouse() == nullptr)
		focusedUi = nullptr;
	if (App->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
		focusedUi = FocusNextElement(focusedUi);
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		if (focusedUi != nullptr&&focusedUi->Module != nullptr) {
			focusedUi->Module->ui_callback(focusedUi);
		}
	Update_Ui();
	Draw_Ui();
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	App->tex->UnLoad(atlas);
	DeleteAllUiElements();
	return true;
}

// const getter for atlas
const SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

void j1Gui::DeleteAllUiElements() {
	eastl::list <UiElement*> ::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end(); it++)
	{
		delete (*it);
	}
	UiElementList.clear();
}

void j1Gui::RemoveUiElement(UiElement* element) {
	RemoveUiChilds(element);
	eastl::list<UiElement*>::iterator it = eastl::find(UiElementList.begin(), UiElementList.end(), element);
	if (it != UiElementList.end()) {
		delete (*it);
		UiElementList.erase(it);
	}
}

void j1Gui::RemoveUiChilds(UiElement* element)
{
	eastl::list<UiElement*>::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end();) {
		if ((*it)->parent == element) {
			App->gui->RemoveUiChilds((*it));
			delete (*it);
			it = UiElementList.erase(it);
		}
		else
			it++;
	}
}

void j1Gui::Update_Ui() {
	int dx, dy;
	App->input->GetMouseMotion(dx, dy);
	eastl::list <UiElement*> ::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end(); it++)
	{
		(*it)->Update(dx, dy);
	}
}

void j1Gui::Draw_Ui() {
	eastl::list <UiElement*> ::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end(); it++)
	{
		(*it)->Draw(atlas);
	}
}

UiElement* j1Gui::UiUnderMouse() {
	int x, y;
	App->input->GetMousePosition(x, y);
	/*if (App->scene->IsEneabled()) {
		x -= App->render->camera.x;
		y -= App->render->camera.y;
	}*/
	UiElement*Element = nullptr;
	eastl::list <UiElement*> ::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end(); it++)
	{
		if ((*it)->GetScreenPos().x < x && x < (*it)->GetScreenPos().x + (*it)->GetScreenRect().w && (*it)->GetScreenPos().y < y && y < (*it)->GetScreenPos().y + (*it)->GetScreenRect().h && ((*it)->interactuable || (*it)->draggable))
			Element = (*it);
	}
	return Element;
}

bool j1Gui::MouseClick() {
	return (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN);
}

void j1Gui::DraggUiElements(UiElement*parent, int dx, int dy) {
	eastl::list <UiElement*> ::iterator it;
	for (it = UiElementList.begin(); it != UiElementList.end(); it++)
	{
		if ((*it)->parent == parent) {
			(*it)->SetLocalPos((*it)->GetLocalPos().x + dx, (*it)->GetLocalPos().y + dy);
			DraggUiElements((*it), dx, dy);
		}
	}
}

UiElement*j1Gui::FocusNextElement(UiElement*current_element) {
	if (current_element == nullptr) {
		eastl::list <UiElement*> ::iterator it;
		for (it = UiElementList.begin(); it != UiElementList.end(); it++)
		{
			if ((*it)->interactuable)
				return (*it);
		}
	}
	else {
		bool iteration = true;
		eastl::list <UiElement*> ::iterator item = eastl::find(UiElementList.begin(), UiElementList.end(), current_element);
		++item;
		for (; item != UiElementList.end(); item++)
		{
			if ((*item)->interactuable)
				return (*item);
			if (item.next() == UiElementList.end() && iteration) {
				iteration = false;
				item = UiElementList.begin();
				if ((*item)->interactuable)
					return (*item);
			}
		}
	}
	return nullptr;
}

UiElement* j1Gui::AddImage(int x, int y, SDL_Rect source_rect, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) {
	UiElement* Image = new UiImage(x, y, source_rect, interactuable, draggeable, parent, elementmodule);
	UiElementList.push_back(Image);
	return Image;
}

UiElement* j1Gui::AddText(int x, int y, const char*text, _TTF_Font*font, SDL_Color color, int size, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) {
	UiElement* Text = new UiText(x, y, text, size, color, interactuable, draggeable, font, parent, elementmodule);
	UiElementList.push_back(Text);
	return Text;
}

UiElement* j1Gui::AddButton(int x, int y, SDL_Rect source_unhover, SDL_Rect source_hover, SDL_Rect source_click, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) {
	UiElement* Button = new UiButton(x, y, source_unhover, source_hover, source_click, interactuable, draggeable, parent, elementmodule);
	UiElementList.push_back(Button);
	return Button;
}

UiElement* j1Gui::AddEntityButton(int x, int y, SDL_Rect source_unhover, SDL_Rect source_hover, SDL_Rect source_click, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) {
	UiElement* EButton = new UiEntityButton(x, y, source_unhover, source_hover, source_click, interactuable, draggeable, parent, elementmodule);
	UiElementList.push_back(EButton);
	return EButton;
}


UiElement::UiElement(int x, int y, int w, int h, bool interactuable, bool draggeable, UiTypes uitype, UiElement* parent, j1Module* elementmodule) : type(uitype), parent(parent), Module(elementmodule), ui_rect({ x,y,w,h }), interactuable(interactuable), draggable(draggeable) { if (parent != nullptr)SetLocalPos(x, y); }

UiElement::~UiElement() {};

const iPoint UiElement::GetScreenPos() {
	iPoint position(ui_rect.x, ui_rect.y);
	return position;
}

const iPoint UiElement::GetLocalPos() {
	if (parent == nullptr) {
		iPoint position(ui_rect.x, ui_rect.y);
		return position;
	}
	else {
		iPoint position(ui_rect.x - parent->GetScreenPos().x, ui_rect.y - parent->GetScreenPos().y);
		return position;
	}
}

const SDL_Rect UiElement::GetScreenRect() {
	return ui_rect;
}

const SDL_Rect UiElement::GetLocalRect() {
	return { GetLocalPos().x,GetLocalPos().y,ui_rect.w,ui_rect.h };
}

void UiElement::SetLocalPos(int x, int y) {
	if (parent == nullptr) {
		ui_rect.x = x; ui_rect.y = y;
	}
	else {
		ui_rect.x = parent->GetScreenPos().x + x;
		ui_rect.y = parent->GetScreenPos().y + y;
	}
}bool UiElement::outofparent() {
	return (GetScreenPos().x + GetScreenRect().w*0.5f<parent->GetScreenPos().x || GetScreenPos().x>parent->GetScreenPos().x + parent->GetScreenRect().w - GetScreenRect().w*0.5 || GetScreenPos().y + GetScreenRect().h*0.5f<parent->GetScreenPos().y || GetScreenPos().y>parent->GetScreenPos().y + parent->GetScreenRect().h - GetScreenRect().h*0.5f);
}



UiImage::UiImage(int x, int y, SDL_Rect source_rect, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) :UiElement(x, y, source_rect.w, source_rect.h, interactuable, draggeable, UiTypes::Image, parent, elementmodule), atlas_rect(source_rect) {}
UiImage::~UiImage() {}

void UiImage::Update(int dx, int dy) {
	//fer que la imatge es mogui amb la camera
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->gui->focusedUi == this)
		App->gui->focusedUi = nullptr;
	if (App->gui->MouseClick() && App->gui->focusedUi == this)
		App->gui->focusedUi = nullptr;
	if (draggable && App->gui->MouseClick() && App->gui->UiUnderMouse() == this && dx != 0 && dy != 0) {
		SetLocalPos(GetLocalPos().x + dx, GetLocalPos().y + dy);
		App->gui->DraggUiElements(this, dx, dy);
	}
}

void UiImage::Draw(SDL_Texture* atlas) {
	if (parent == nullptr || !outofparent())
		App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &atlas_rect,false);
}

UiText::UiText(int x, int y, const char*text, int size, SDL_Color color, bool interactuable, bool draggeable, _TTF_Font*font, UiElement* parent, j1Module* elementmodule) : UiElement(x, y, size, size, interactuable, draggeable, UiTypes::Text, parent, elementmodule), font_type(font), message(text), color(color), texture(App->font->Print(message, color, font_type)) {}
UiText::~UiText() {}

void UiText::Draw(SDL_Texture* atlas) {
	if (parent == nullptr || !outofparent())
		App->render->Blit(texture, GetScreenPos().x, GetScreenPos().y, NULL,false);
}

void UiText::Update(int dx, int dy) {
	//fer que el text es mogui amb la camera
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->gui->focusedUi == this)
		App->gui->focusedUi = nullptr;
	if (App->gui->MouseClick() && App->gui->focusedUi == this)
		App->gui->focusedUi = nullptr;
	if (draggable && App->gui->MouseClick() && App->gui->UiUnderMouse() == this && dx != 0 && dy != 0) {
		SetLocalPos(GetLocalPos().x + dx, GetLocalPos().y + dy);
		App->gui->DraggUiElements(this, dx, dy);
	}
}

UiButton::UiButton(int x, int y, SDL_Rect source_unhover, SDL_Rect source_hover, SDL_Rect source_click, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) :UiElement(x, y, source_unhover.w, source_unhover.h, interactuable, draggeable, UiTypes::Button, parent, elementmodule), unhover(source_unhover), hover(source_hover), click(source_click), current_state(Button_state::unhovered) {}
UiButton::~UiButton() {}

void UiButton::Update(int dx, int dy) {
	if (App->gui->focusedUi == this)
		current_state = Button_state::hovered;
	else if (App->gui->UiUnderMouse() == this)
		current_state = Button_state::hovered;
	else
		current_state = Button_state::unhovered;
	if (App->gui->MouseClick() && App->gui->focusedUi == this) {
		current_state = Button_state::clicked;
		App->gui->focusedUi = nullptr;
	}
	if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && App->gui->focusedUi == this) {
		current_state = Button_state::clicked;
		App->gui->focusedUi = nullptr;
	}
	if (draggable && App->gui->MouseClick() && App->gui->UiUnderMouse() == this && dx != 0 && dy != 0) {
		SetLocalPos(GetLocalPos().x + dx, GetLocalPos().y + dy);
		App->gui->DraggUiElements(this, dx, dy);
	}
}

void UiButton::Draw(SDL_Texture*atlas) {
	if (parent == nullptr || !outofparent()) {
		switch (current_state) {
		case Button_state::unhovered:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &unhover,false);
			break;
		case Button_state::hovered:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &hover,false);
			break;
		case Button_state::clicked:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &click,false);
			break;
		}
	}
}

UiEntityButton::UiEntityButton(int x, int y, SDL_Rect source_unhover, SDL_Rect source_hover, SDL_Rect source_selected, bool interactuable, bool draggeable, UiElement* parent, j1Module* elementmodule) :UiElement(x, y, source_unhover.w, source_unhover.h, interactuable, draggeable, UiTypes::EButton, parent, elementmodule), unhover(source_unhover), hover(source_hover), click(source_selected),current_state(Button_state::unhovered),selected(false) {}

UiEntityButton::~UiEntityButton(){}

void UiEntityButton::Update(int dx, int dy) {
	if (App->gui->focusedUi == this) {
		if (selected)
			current_state = Button_state::clicked;
		else
			current_state = Button_state::hovered;
	}
	else if (App->gui->UiUnderMouse() == this) {
		if (selected)
			current_state = Button_state::clicked;
		else
			current_state = Button_state::hovered;
	}
	else {
		if (selected)
			current_state = Button_state::clicked;
		else
			current_state = Button_state::unhovered;
	}
	if ((App->gui->MouseClick() || App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && App->gui->focusedUi == this) {
		selected = !selected;
		if (selected)
			current_state = Button_state::clicked;
		else {
			current_state = Button_state::unhovered;
			App->gui->focusedUi = nullptr;
		}
	}
	else if ((App->gui->MouseClick() || App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN) && App->gui->focusedUi != this) {
		selected = false;
		current_state = Button_state::unhovered;
	}
	if (draggable && App->gui->MouseClick() && App->gui->UiUnderMouse() == this && dx != 0 && dy != 0) {
		SetLocalPos(GetLocalPos().x + dx, GetLocalPos().y + dy);
		App->gui->DraggUiElements(this, dx, dy);
	}
}

void UiEntityButton::Draw(SDL_Texture* atlas) {
	if (parent == nullptr || !outofparent()) {
		switch (current_state) {
		case Button_state::unhovered:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &unhover, false);
			break;
		case Button_state::hovered:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &hover, false);
			break;
		case Button_state::clicked:
			App->render->Blit(atlas, GetScreenPos().x, GetScreenPos().y, &click, false);
			break;
		}
	}
}