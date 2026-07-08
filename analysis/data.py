import sys

sys.path.append("D:/Projects/eu4gamereview/EU4GameReview/build")

try:
    import eu4tools  # type: ignore
except Exception as error:
    print(f"Error importing the required module: {error}")
    sys.exit(0)


def load(path: str):
    return eu4tools.parse(path)


class Country:
    def __init__(self, name):
        self.name = name
