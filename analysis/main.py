import get_basic_info

credentials: tuple[str, str] = get_basic_info.getBasic()
print(
    f"You're playing as the {credentials[0]} at the date {credentials[1][2]}.{credentials[1][1]}.{credentials[1][0]}"
)
