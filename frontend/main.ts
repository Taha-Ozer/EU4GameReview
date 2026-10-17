import {type Country, type RawBaseData} from "./types.js";
import {readData} from "./DataFetcher.js";
import {renderPlayer} from "./PlayerRenderer.js";


document.addEventListener('DOMContentLoaded', async () => {
    let data: RawBaseData | null = await readData("../../data/data.json");
    if (!data){
        console.log("Couldn't read file");
    }
    else{
        const name: HTMLElement | null = document.getElementById("player-name");
        if (!name){
            console.log("Couldn't fetch player name");
            return;
        }
        else{
            renderPlayer(data.player);
        }
    }
})