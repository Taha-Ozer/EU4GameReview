def getBasic(data: dict) -> tuple:
    playerTag: str = data["player"]
    money = data["countries"][playerTag]["treasury"]
    date: tuple = data["date"]
    player: str = data["displayed_country_name"]
    return (player, date, money)
