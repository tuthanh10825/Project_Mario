#pragma once
namespace Textures {
	enum ID {
		Background1,
		Background2,
		Background3,
		TitleBackground,
		SaveGameBackground,
		Title,
		PlayButton,
		ExitButton,
		ContinueButton,
		SettingButton,
		WoodenBox,
		Level1,
		Level2,
		Level3,
		Back,
		Arrow,
		Character1,
		Character2,
		Block,
		Char1MovRight,
		Char1MovLeft,
		Char2MovRight,
		Char2MovLeft,
		Goomba,
		GoombaMove,
		GoombaDead,
		Mushroom,
		FireFlower,
		Coin,
		Heart,
		Bullet,
		BulletAnimation,
		Char1Select,
		Char2Select,
		BlockTileset,
		MysteryBlock, 
		PlantMove,
		Plant,
		Bird,
		BirdMovRight,
		BirdMovLeft,
		Win,	
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
		Pause,
		Death,
		Win, 
		Continue, 
		Settings,

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
		SceneNodeSound = 1 << 9, 
	};
}
enum Level {
	None = 0,
	Easy = 1, 
	Medium = 2, 
	Hard = 3,
};

enum Characters{
	CharNone = 0,
	Character1 = 1,
	Character2 = 2,
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
namespace Music {
	enum ID {
		MenuTheme, 
	};
}
namespace SoundEffect {
	enum ID {
		Jump, 
		Pause, 
		ChangeOption, 
		Fire, 
		Die,
		Win,
		CreateMushroom, 
		CreateFlower, 
		CreateCoin, 
		EnemyDeath, 
		CharacterDeath, 
		GetPickup, 
	};
}