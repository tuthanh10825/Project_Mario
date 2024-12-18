#pragma once
namespace Textures {
	enum ID {
		Background, 
		TitleBackground,
		Title,
		PlayButton,
		ExitButton,
		Level1,
		Level2,
		Level3,
		Back,
		Arrow,
		Character1, 
		Block,
		MovRight,
		MovLeft,
		Goomba,
		GoombaMovRight,
		GoombaMovLeft,
		GoombaDead,
		Pickup,
		Heart,
		Projectile,
	};
}

namespace Fonts {
	enum ID {
		PixeloidMono,
		PixeloidSans,
		PixeloidSansBold,
	};


}

namespace Buttons {
	enum ID {
		Play,
		SelectedPlay,
		Exit,
		SelectedExit,
	};
}


namespace States {
	enum ID {
		None,
		Menu, 
		LevelSelect,
		Game, 
		Pause
	};
}
namespace Category {
	enum Type {
		None = 0, 
		Scene = 1 << 1,
		Player = 1 << 2, 
		Enemy = 1 << 3, 
		Block = 1 << 4,
		MysteryBlock = 1 << 5,
		Pickup = 1 << 6, 
		SceneNodeAir =  1 << 7, 
		Projectile = 1 << 8,
	};
}
enum Level {
	None = 0,
	Easy = 1, 
	Medium = 2, 
	Hard = 3,

};

namespace Collision {
	enum Direction {
		None = 0,
		Up = 1,
		Down = 1 << 1,
		Left = 1 << 2,
		Right = 1 << 3
	};
}