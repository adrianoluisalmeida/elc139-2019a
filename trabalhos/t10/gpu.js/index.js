const c = document.getElementById('c');
const SIZE_A = 512;
const SIZE_B = 512;

const gpu = new GPU({
    mode: 'gpu'
});

const gpuMatMult = gpu.createKernel(function (A, B) {
        var sum = 0;
        for (var i = 0; i < 512; i++) {
            sum += A[this.thread.y][i] * B[i][this.thread.x];
        }
        return sum;
    })
    .setDimensions([SIZE_A, SIZE_B])
    .setOutputToTexture(true);

function cpuMatMult(m, n) {
    var result = [];
    for (var i = 0; i < m.length; i++) {
        result[i] = [];
        for (var j = 0; j < n[0].length; j++) {
            var sum = 0;
            for (var k = 0; k < m[0].length; k++) {
                sum += m[i][k] * n[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

// Generate Matrices
const matrices = generateMatrices();
const A = matrices.A;
const B = matrices.B;
console.log("Matriz A tam. " + A.length,  " Matriz B tam. " + B.length);

//CPU
const startCPU = window.performance.now();
const cpuResult = cpuMatMult(A, B);
const endCPU = window.performance.now();
const cpuTime = endCPU - startCPU;
console.log(`CPU: ${cpuTime}ms`);

//GPU
const startGPU = window.performance.now();
const result = gpuMatMult(A, B);
const endGPU = window.performance.now();
const gpuTime = endGPU - startGPU;
console.log(`GPU: ${gpuTime}ms`);

//Diff
const diff = (cpuTime - gpuTime) / (gpuTime);
console.log(`%c ${diff}`, 'color: red;', `vezes mais rápido!!!`)

/**
 * adiciona 512 * 512 elementos em uma matriz JavaScript. (1D)  e, em seguida, divide-os em 512 partes, o que significa que, no final ,
 * temos um array 2D de tamanho 512*512. (Cada elemento da matriz tem elementos filhos.)
 */
function generateMatrices() {
    const matSize = 512;
    let A = [];
    let B = [];
    for (let n = 0; n < matSize * matSize; n++) {
        const randA = Math.random();
        const randB = Math.random();
        A.push(randA);
        B.push(randB);
    }

    A = splitArray(A, matSize);
    B = splitArray(B, matSize);

    function splitArray(array, part) {
        var tmp = [];
        for (var i = 0; i < array.length; i += part) {
            tmp.push(array.slice(i, i + part));
        }
        return tmp;
    }

    return {
        A,
        B
    };
}