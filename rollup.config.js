import peerDepsExternal from "rollup-plugin-peer-deps-external";
import resolve from "@rollup/plugin-node-resolve";
import commonjs from "@rollup/plugin-commonjs";
import typescript from "rollup-plugin-typescript2";

const packageJson = require("./package.json");
const globals = {
    ...packageJson.devDependencies,
};

export default {
    input: "./src/app.ts",
    output: {
        file: "./dist/bundle.cjs",
        format: "cjs"
    },
    plugins: [
        peerDepsExternal(),
        resolve(),
        commonjs(),
        typescript(),
        commonjs({
            exclude: "node_modules",
            ignoreGlobal: true,
        })
    ],
    external: Object.keys(globals),
};
