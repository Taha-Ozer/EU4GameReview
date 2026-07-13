def getBasic(data: dict) -> tuple:
    playerTag: str = data["player"]
    date: tuple = data["date"]
    player: str = data["displayed_country_name"]
    return (player, date, playerTag)
