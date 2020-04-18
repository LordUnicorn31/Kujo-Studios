/*#include "Animation.h"

SDL_Rect& Animation::GetCurrentFrame(float dt) {
	current_frame_time += dt;
	if (frames->duration < current_frame_time) {
		current_frame += 1;
		current_frame_time = 0.0f;
	}
	if (current_frame >= total_frames)
		current_frame = 0;
	return frames[current_frame].rect;
}

SDL_Rect& Animation::DoOneLoop(float dt) {
	current_frame_time += dt;
	if (frames->duration < current_frame_time) {
		current_frame += 1;
		current_frame_time = 0.0f;
	}
	if (current_frame >= total_frames)
		current_frame = total_frames - 1;
	return frames[current_frame].rect;
}
*/


/*
entity_node = entity_node.child("tile");

LOG("Loading entity animations");
for (entity_node; entity_node; entity_node = entity_node.next_sibling("tile")) {
	Animation* animation = new Animation();
	animation->name.create(entity_node.child("properties").child("property").attribute("value").as_string());
	animation->total_frames = entity_node.child("properties").child("property").next_sibling("property").attribute("value").as_uint();
	LOG("Loading %s animation with %d frames", animation->name.GetString(), animation->total_frames);
	animation->texture = sprite_tilesets.start->data->texture;
	pugi::xml_node frame_node = entity_node.child("animation").child("frame");
	animation->frames = new Frame[animation->total_frames];
	for (int i = 0; i < animation->total_frames; frame_node = frame_node.next_sibling("frame"), ++i) {
		uint tileset_id = frame_node.attribute("tileid").as_uint();
		animation->frames[i].duration = frame_node.attribute("duration").as_float() / 1000;//Dividir entre 1000 pk sigui canvi de frame de l0'animacio en cada segon (esta en milisegons en el tmx)
		animation->frames[i].rect = sprite_tilesets.start->data->TilesetRect(tileset_id + 1);//pk el +1??? pk la funcio tilesetrect conta el primer tile com si fos un 1 i no el zero
	}
	Animations.add(animation);
	LOG("Succesfully loaded %s animation", animation->name.GetString());
*/