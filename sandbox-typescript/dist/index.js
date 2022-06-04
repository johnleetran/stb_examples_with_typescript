var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import STBModule from './wasm/stb.js';
function isSTBup() {
    let btn = document.createElement("button");
    btn.innerHTML = "isSTBup";
    btn.addEventListener("click", () => __awaiter(this, void 0, void 0, function* () {
        let STB = yield STBModule();
        STB.isitup();
        let d0 = new STB.dummy_data("myKey", 420);
        let v = new STB.dummy_vector(d0);
        let d1 = new STB.dummy_data("anotherKey", 69);
        v.push(d1);
        console.log(v.get(0));
        console.log(v.get(1));
    }));
    document.body.appendChild(btn);
}
isSTBup();
