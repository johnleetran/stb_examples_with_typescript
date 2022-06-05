import STBModule from './wasm/stb.js';

function isSTBup(){
    let btn = document.createElement("button");
    btn.innerHTML = "isSTBup";
    btn.addEventListener("click", async () => {
        let STB = await STBModule();
        STB.isitup();
        let d0 = new STB.dummy_data("myKey", 420);
        let v = new STB.dummy_vector(d0);

        let d1 = new STB.dummy_data("anotherKey", 69);
        v.push(d1);
        console.log(v.get(0));
        console.log(v.get(1));

    });
    document.body.appendChild(btn);
}

isSTBup();

