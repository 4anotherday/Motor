-- How to define game objects in the scene file
-- Step1: HowManyGameObjects must contain one more number than the last go_X that was declared because these start at 0
-- 		  If you want to add a go add one to this variable
-- Step2: Structure
--  go_Number = {}   								-> where "Number" is the next to the last go declared
--  go_Number[0] = { Name = "", HowManyCmps = X}	-> Name is the name of the GameObject. HowManyCmps is the number of components of the go
--  go_Number[1] = { Component = " ", General Data} -> Component is the ENUM used to identify the COMPONENT (getComponentType method from LuaParser). 
--													   General Data is the component data

-- You must bear in mind that in the definition of go, the first position of the array will always be the data that it needs to know its name 
-- and how many components it has. The following positions in the array will be used to define the components

-- You can find component definition examples at the end of this document

HowManyGameObjects = 5

go_0 = {}
go_0[0] = { Name = "Camara", HowManyCmps = 2, Persist = false}
go_0[1] = { Component = "Transform", Coord = {X = 0, Y = 2, Z = -8}, Rotation={X=0, Y=180, Z=0}}
go_0[2] = { Component = "Camera", SlaveRotation = false, Plane = {Near = 1, Far = 9999},
			Projection = true, Fovy = 60, Frustrum = {Left = 1, Right = 1, Top = 1, Bot = 1}, 
			OrthoWindow = {W = 100, H = 100}, Viewport = {Left = 0, Top = 0, W = 1, H = 1},
			DisplayOverlays= true, zOrder = 1, Compositors = { "JugadorVisionWeak", false, "JugadorVisionStrong", false }}
			
go_1 = {}
go_1[0] = { Name = "Luz", HowManyCmps = 2, Persist = false}
go_1[1] = { Component = "Transform", Coord = {X = 4, Y = 4, Z = 0}}
go_1[2] = { Component = "LightComponent", LightType= "SPOTLIGHT", Visible = true, Intensity = 1,
			LightDirection = {X = -2, Y = -1, Z = 0},
			Attenuation = {Range = 100, Constant = 1, Linear = 0.045, Quadratic = 0.0075},
			Diffuse = {Red = 1, Green= 1, Blue = 1}, 
			Specular = {Red = 1, Green= 1, Blue = 1}}

go_2 = {}
go_2[0] = { Name = "Suelo", HowManyCmps = 2, Persist = false}
go_2[1] = { Component = "Transform", Coord = {X = 0, Y = 0, Z = 0}, Rotation={X=0, Y=0, Z=0}, Scale = { X=10, Y=1, Z=10}}
go_2[2] = { Component = "RenderObject", MeshName="cube.mesh", Material="Practica1/Metal",
   			Visible=true, Shadows=true, RenderingDistance = 1000}
-- go_2[3] = { Component = "BoxCollider"}


go_3 = {}
go_3[0] = { Name = "Objeto1", HowManyCmps = 2, Persist = false}
go_3[1] = { Component = "Transform", Coord = {X = -2, Y = 2, Z = 0}, Rotation={X=0, Y=0, Z=0}, Scale = {X=1, Y=4, Z=1}}
go_3[2] = {	Component = "RenderObject", MeshName="cube.mesh", Material="Practica1/Metal",
			 Visible=true, Shadows=true, RenderingDistance = 1000}
go_3[3] = { Component = "RigidBody", Static = true, Type = "Box", Kinematic = false, Mass = 1}


go_4 = {}
go_4[0] = { Name = "Objeto2", HowManyCmps = 1, Persist = false}
go_4[1] = { Component = "Transform", Coord = {X = 2, Y = 2, Z = 0}, Rotation={X=0, Y=0, Z=0}, Scale = {X=1, Y=4, Z=1}}
go_4[2] = {	Component = "RenderObject", MeshName="cube.mesh", Material="Practica1/Metal",
			 Visible=true, Shadows=true, RenderingDistance = 1000}
go_4[3] = { Component = "RigidBody", Static = true, Type = "Box", Kinematic = false, Mass = 1}			 





-- go_2 = {}
-- go_2[0] = { Name = "DarkLight", HowManyCmps = 2}
-- go_2[1] = { Component = "Transform", Coord = {X = 0, Y = 0, Z = 0}}
-- go_2[2] = { Component = "LightComponent", LightType= "POINT", Visible = true, Diffuse = {Red = 1, Green= 1, Blue = 1}, 
-- 	   		Specular = {Red = 1, Green= 1, Blue = 1},
-- 			Attenuation = {Range = 1, Constant = 1, Linear = 1, Quadratic = 1},
-- 			SpotLightRange = {InnerAngle = 1, OuterAngle = 1, FallOf = 1}}

-- go_3={}
-- go_3[0] ={Name ="AverSiPeta" , HowManyCmps=5,Persist=false}
-- go_3[1]={ Component = "Transform", Coord = {X = 0, Y = 0, Z = -200}}
-- go_3[2] = {	Component = "RenderObject", MeshName="cube.mesh", Material="Practica1/Yellow", 
-- 			RotateAngle = 0, Rotate={X=0, Y=0, Z=0}, Scale = {X=1, Y=1, Z=1}, LookAt ={X=1, Y=1, Z=1},
-- 			Visible=true, Shadows=true, RenderingDistance = 1000}
-- go_3[3] = { Component = "RigidBody", Type="Box",Mass=9,Width=20,Depth=20,Height=100}
-- go_3[4] = { Component = "AudioSource", Route = {"./src", "./src2", "./feo"}}
-- go_3[5] = { Component = "Listener", ListenerNumber = 0, Velocity = {X = 1, Y = 0, Z = 5}, Forward = {X = 3, Y = 2, Z = 1}, Up = {X = 8, Y = 7, Z = 9}}

-- go_3 = {}
-- go_3[0] = { Name = "ImageR", HowManyCmps = 2, Persist = false}
-- go_3[1] = { Component = "Transform", Coord = {X = 0, Y = 0, Z = 0}}
-- go_3[2] = { Component = "ImageRenderer", DefaultDimension = {W = 1, H = 2}, 
-- 			MaterialName = "Practica1/Yellow", Visible = true, 
-- 			BillboardOrigin = "BBO_TOP_LEFT", BillboardType = "BBT_POINT",
-- 			BillboardRotationType = "BBR_VERTEX",
-- 			Scale = {X = 1, Y = 1, Z = 1}, Rotation = {X = 1, Y = 2, Z = 3, Angle = 0}}
-- go_3 = {}
-- go_3[0] = { Name = "Cam", HowManyCmps = 2, Persist = false}
-- go_3[1] = { Component = "Transform", Coord = {X = 400, Y = 80, Z = 0}}
-- go_3[2] = { Component = "Camera", Orientation = {X = 0, Y = 0, Z = -1}, Plane = {Near = 1, Far = 9999},
-- 			Projection = true, Fovy = 6, Frustrum = {Left = 4, Right = 3, Top = 2, Bot = 1}, 
-- 			OrthoWindow = {W = 8, H = 9}, Viewport = {Left = 0.5, Top = 0, W = 0.5, H = 1},
-- 			DisplayOverlays= true, zOrder = 2}


-- COMPONENT EXAMPLES

-- Transform 		-> go_goNumber[componentNumber] = { Component = "Transform", Coord = {X = 1, Y = 1, Z = 1}}

-- AudioSource 		-> go_goNumber[componentNumber] = { Component = "AudioSource", Route ={"./src", "./src2"}}

-- LightComponent	-> go_goNumber[componentNumber] = { Component = "LightComponent", LightType= "POINT", Visible = false,
--														Diffuse = {Red = 1, Green= 1, Blue = 1} 
--														Specular = {Red = 1, Green= 1, Blue = 1}
--														Attenuation = {Range = 1, Constant = 1, Linear = 1, Quadratic = 1}
--														SpotLightRange = {InnerAngle = 1, OuterAngle = 1, FallOf = 1}}

-- ListenerComponent-> go_goNumber[componentNumber] = { Component = "Listener", ListenerNumber = 0, 
--														Velocity = {X = 1, Y = 0, Z = 5}, Forward = {X = 3, Y = 2, Z = 1}, Up = {X = 8, Y = 7, Z = 9}}

-- AnimatorComponent-> go_goNumber[componentNumber] = { Component = "Animator", HowManyStates = 2,
--														State1 = {Name = "initial", Loop = true},
--														State2 = {Name = "second", Loop = false},
--														StateN = {Name = "anotherOne", Loop = "true"}}

-- ButtonComponent	-> go_goNumber[componentNumber] = { Component = "ButtonComponent", Active = false, OverLayName="ovName", ContainerName= "SexyContainer", 
--														DefaultMaterial = "defaultMaterial", HoverMaterial = "hoverMaterial", PressMaterial = "pressMaterial"}

-- CameraComponent  -> go_goNumber[componentNumber] = { Component = "Camera", Orientation = {X = 3, Y = 2, Z = 1}, 
--    Projection (F = orthographic, T = perspective)	Plane = {Near = 2, Far = 9999}, Projection = true, Fovy = 6, 
--								 						Frustrum = {Left = 4, Right = 3, Top = 2, Bot = 1}, 
--								 						OrthoWindow = {W = 8, H = 9}, Viewport = {Left = 9, Top = 8, W = 7, H = 6}}

-- Overlay 			-> go_goNumber[componentNumber] = { Component = "OverlayComponent", Hide=true, Name = "SexyOverlay", Container = "SexyContainer", Material= "SexyOverlaymMaterial"}

-- RenderObject 	-> go_goNumber[componentNumber] = { Component = "RenderObject", MeshName="SexyMesh", Material="SexyMaterial", 
--														RotateAngle = 1, Rotate={X=1, Y=1, Z=1}, Scale = {X=1, Y=1, Z=1}, LookAt ={X=1, Y=1, Z=1},
--														Visible=false, Shadows=false, RenderingDistance = 1}

-- ImageRender      -> go_goNumber[componentNumber] = { Component = "ImageRenderer", DefaultDimension = {W = 1, H = 2}, 
--														MaterialName = "SoyFeo", Visible = false, 
--														BillboardOrigin = "BBO_TOP_LEFT", BillboardType = "BBT_POINT",
--														BillboardRotationType = "BBR_VERTEX",
--														Scale = {X = 0.3, Y = 0.5, Z = 1}, Rotation = {X = 1, Y = 2, Z = 3, Angle = 180}}

-- PartycleSystem 	-> go_goNumber[componentNumber] = { Component = "ParticleSystem", Path="SexyPath"}

-- RigidBody with Spere collider -> go_goNumber[componentNumber] = { Component = "RigidBody", Radius=5 }
