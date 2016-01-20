plane = 0.004802 y + 0.007480 x + 8.554271 z;
Print[
    FindInstance[
        plane > 5 && -50 <= x && x <= 75 && 150 <= y && y <= 200,
		{x,y,z},
		Reals
    ]
]
