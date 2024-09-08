from json import *

class Sommet:
	def __init__(self, s_id: int, name: str, x: float, y: float, z: float):
		self.id: int = s_id
		self.name: str = name
		self.x: float = x
		self.y: float = y
		self.z: float = z

	def __repr__(self) -> str:
		return f"{self.id}\t{self.name}\t{self.x}\t{self.y}\t{self.z}"

class Lien:
	UNI: int = 1
	BI: int = 2

	def __init__(self, idA: int, idB: int, mode: int) -> None:
		self.idA: int = idA
		self.idB: int = idB

		self.mode: int = mode

	def __repr__(self) -> str:
		return f"{self.idA}\t{self.idB}\t{self.mode}"

CorrSommets: dict[str: int] = {}
Sommets: list[Sommet] = []
Liens: list[Lien] = []

def ParseSommets(filepath: str):
	global Sommets, CorrSommets

	f = open(filepath, "r")

	raw: dict = load(f)

	if not f.closed:
		f.close()
		del f

	if ("Dots" in raw.keys()):
		Id: int = 0

		Dots: dict = raw["Dots"]

		for name in Dots.keys():
			name: str = name

			dot: dict[str: float] = Dots[name]

			coords: tuple[float] = dot["x"], dot["y"], dot["z"]

			Sommets.append(Sommet(Id, name, *coords))
			CorrSommets[name] = Id
			Id += 1

	Sommets.sort(key=lambda x: x.id)

def ParseLiens(filepath: str):
	global Liens

	f = open(filepath, "r")

	raw: dict = load(f)

	if not f.closed:
		f.close()
		del f

	if ("Segments" in raw.keys()):
		Segs: list[str] = raw["Segments"]

		for lien in Segs:
			nameA, sep, nameB = lien.split(" ")

			mode: int = 0

			if (sep == "-"):
				mode = Lien.UNI
			elif (sep == ">"):
				mode = Lien.BI
			else:
				raise Exception("Unknown separator for \"{lien}\"")

			idA: int = CorrSommets[nameA]
			idB: int = CorrSommets[nameB]

			Liens.append(Lien(nameA, nameB, mode))

	Liens.sort(key=lambda x: x.idA)

def ParseAll(filepath: str):
	ParseSommets(filepath)
	ParseLiens(filepath)

def ExportSommets(basename: str):
	f = open(f"{basename}_s.csv", "w")

	for s in Sommets:
		f.write(f"{s}\n")

	f.close()

def ExportLiens(basename: str):
	f = open(f"{basename}_l.csv", "w")

	for l in Liens:
		f.write(f"{l}\n")

	f.close()

def ExportAll(basename: str):
	ExportSommets(basename)
	ExportLiens(basename)

ParseAll("France.json")
ExportAll("France")