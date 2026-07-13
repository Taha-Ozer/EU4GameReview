def loadLocalisations(path: str) -> dict:
    localisations: dict = {}
    with open(path, "r", encoding="utf-8-sig") as f:
        buffer = f.read()
    line = ""
    for letter in buffer:
        if letter != "\n":
            line += letter
        else:
            if "l_english" in line:
                line = ""
                continue
            if not line:
                continue
            parts = line.split(":")
            country = parts[0].strip()
            nameParts = parts[1].split('"')
            name = nameParts[1]
            localisations[country] = name
            line = ""
    return localisations
