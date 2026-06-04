#pragma once
#include <string>
namespace ANM2 {
	struct AnimationState {
		std::string anim_name = "";
		int cur_frame = 0;
		bool is_finished = false;
		float cur_frame_accumulator=0.0f;
	};
}