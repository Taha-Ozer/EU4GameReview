import pytest
import json
from unittest.mock import mock_open, patch

# Import your modules
from analysis import country, get_basic_info, greatpowers, jsonexport, localisation


# --- FIXTURES (Mock Data) ---
@pytest.fixture
def mock_localisations():
    return {"FRA": "France", "ENG": "Great Britain", "TUR": "Ottoman Empire"}


@pytest.fixture
def mock_save_data():
    return {
        "player": "FRA",
        "date": (1520, 10, 12),
        "displayed_country_name": "France",
        "countries": {
            "FRA": {
                "treasury": 150.5,
                "estimated_monthly_income": 42.0,
                "manpower": 25000,
                "development": 320,
                "army": [
                    {"regiment": [{}, {}, {}]},  # 3 regiments
                    {"regiment": [{}]},  # 1 regiment
                ],
                "navy": {  # Single dict case instead of a list
                    "ship": [{}, {}]  # 2 ships
                },
            },
            "TUR": {
                "treasury": 500.0,
                "estimated_monthly_income": 85.0,
                "manpower": 60000,
                "development": 650,
                "army": [],
                "navy": [],
            },
        },
        "great_powers": {"original": [{"country": "TUR"}, {"country": "FRA"}]},
    }


# --- TESTS: country.py ---
def test_country_todict():
    c = country.Country("FRA", "France", 100.0, 10.0, 5000, 5, 2, 50)
    data_dict = c.toDict()

    assert data_dict["tag"] == "FRA"
    assert data_dict["name"] == "France"
    assert data_dict["treasury"] == 100.0
    assert data_dict["development"] == 50


def test_get_country_army_and_navy_size(mock_save_data):
    fra_data = mock_save_data["countries"]["FRA"]

    # Check army size (handles list of dicts)
    army_size = country.getCountryArmySize(fra_data)
    assert army_size == 4

    # Check navy size (handles single dict edge case)
    navy_size = country.getCountryNavySize(fra_data)
    assert navy_size == 2


def test_get_country_defaults():
    empty_country_data = {}

    assert country.getCountryTreasury(empty_country_data) == 0.0
    assert country.getCountryIncome(empty_country_data) == 0.0
    assert country.getCountryManpower(empty_country_data) == 0
    assert country.getCountryArmySize(empty_country_data) == 0
    assert country.getCountryNavySize(empty_country_data) == 0
    assert country.getCountryDevelopment(empty_country_data) == 0


# --- TESTS: get_basic_info.py ---
def test_get_basic(mock_save_data):
    player_name, date, tag = get_basic_info.getBasic(mock_save_data)
    assert player_name == "France"
    assert date == (1520, 10, 12)
    assert tag == "FRA"


def test_get_player(mock_save_data, mock_localisations):
    player = get_basic_info.getPlayer(mock_save_data, mock_localisations)
    assert isinstance(player, country.Country)
    assert player.tag == "FRA"
    assert player.name == "France"


# --- TESTS: greatpowers.py ---
def test_get_great_powers(mock_save_data, mock_localisations):
    gps = greatpowers.getGreatPowers(mock_save_data, mock_localisations)
    assert len(gps) == 2
    assert gps[0].tag == "TUR"
    assert gps[1].tag == "FRA"


def test_convert_gps(mock_save_data, mock_localisations):
    gps = greatpowers.getGreatPowers(mock_save_data, mock_localisations)
    gp_dicts = greatpowers.convertGps(gps)

    assert isinstance(gp_dicts, list)
    assert len(gp_dicts) == 2
    assert gp_dicts[0]["tag"] == "TUR"


# --- TESTS: jsonexport.py ---
def test_aggregate_player_and_gps(mock_save_data, mock_localisations):
    player = get_basic_info.getPlayer(mock_save_data, mock_localisations)
    gps = greatpowers.getGreatPowers(mock_save_data, mock_localisations)

    aggregated = jsonexport.aggregatePlayerAndGps(player, gps)

    assert "player" in aggregated
    assert "greatPowers" in aggregated
    assert aggregated["player"]["tag"] == "FRA"
    assert len(aggregated["greatPowers"]) == 2


def test_export_countries(tmp_path):
    sample_data = {"player": {"tag": "FRA"}, "greatPowers": []}
    target_file = tmp_path / "data.json"

    # Override open path to use pytest's temporary directory
    with patch("builtins.open", mock_open()):
        with patch("json.dump") as mock_json_dump:
            jsonexport.exportCountries(sample_data)
            mock_json_dump.assert_called_once()


# --- TESTS: localisation.py ---
def test_load_localisations():
    mock_yml = 'l_english:\n FRA:0 "France"\n ENG:0 "Great Britain"\n'

    with patch("builtins.open", mock_open(read_data=mock_yml)):
        locs = localisation.loadLocalisations("dummy_path.yml")
        assert locs.get("FRA") == "France"
        assert locs.get("ENG") == "Great Britain"
