#pragma once
namespace Textures {
	enum ID {
		Background, 
		Character1, 
		Block,
		MovRight,
		MovLeft,
	};
}

namespace Fonts {
	enum ID {
		PixeloidMono,
		PixeloidSans,
		PixeloidSansBold,
	};
}
namespace States {
	enum ID {
		None,
		Menu, 
		Game, 
		Pause
	};
}
namespace Category {
	enum Type {
		None = 0, 
		Scene = 1 << 0, 
		Player = 1 << 1, 
		Enemy = 1 << 2, 
		Block = 1 << 3,
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