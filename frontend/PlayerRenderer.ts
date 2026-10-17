import { type Country, ElementType } from "./types.js";

function putValueInElement(element: string, player: Country, type: ElementType): void{
    const htmlValue: HTMLElement | null = document.getElementById(element);
    if (!htmlValue){
        console.log("Couldn't fetch element\n");
        return;
    }
    switch (type){
        case ElementType.NAME:
            htmlValue.textContent = player.name;
            return;
        case ElementType.DEV:
            htmlValue.textContent = player.development.toFixed(2).toString();
            return;
        case ElementType.INCOME:
            htmlValue.textContent = player.estimated_monthly_income.toFixed(2).toString();
            return;
        case ElementType.TREASURY:
            htmlValue.textContent = player.treasury.toFixed(2).toString();
            return;
        case ElementType.MANPOWER:
            htmlValue.textContent = player.manpower.toFixed(1).toString().concat('k');
            return;
        case ElementType.REGIMENTS:
            htmlValue.textContent = player.regiment_count.toFixed().toString();
            return;
        case ElementType.SHIPS:
            htmlValue.textContent = player.ship_count.toFixed().toString();
            return;
    }
}

export function renderPlayer(player: Country): void{
    putValueInElement("player-name", player, ElementType.NAME);
    putValueInElement("development", player, ElementType.DEV)
    putValueInElement("income", player, ElementType.INCOME);
    putValueInElement("treasury", player, ElementType.TREASURY);
    putValueInElement("manpower", player, ElementType.MANPOWER);
    putValueInElement("regiment-count", player, ElementType.REGIMENTS);
    putValueInElement("ship-count", player, ElementType.SHIPS);
}