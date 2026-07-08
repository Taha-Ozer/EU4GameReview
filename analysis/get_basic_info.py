import analysis.data as data


def getBasic():
    eu4data = data.load(
        "C:\\Users\\Taha\\Documents\\Paradox Interactive\\Europa Universalis IV\\save games\\zoroaustrianss.eu4"
    )
    date = eu4data["date"]
    player = eu4data["displayed_country_name"]
    return (player, date)
