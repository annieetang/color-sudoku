import logo from './logo.svg';
import React, { useState } from 'react';
import './App.css';

var grid = [
    [0, 5, 0, 9, 0, 0, 0, 0, 0],
    [8, 0, 0, 0, 4, 0, 3, 0, 7],
    [0, 0, 0, 2, 8, 0, 1, 9, 0],
    [5, 3, 8, 6, 0, 7, 9, 4, 0],
    [0, 2, 0, 3, 0, 1, 0, 0, 0],
    [1, 0, 9, 8, 0, 4, 6, 2, 3],
    [9, 0, 7, 4, 0, 0, 0, 0, 0],
    [0, 4, 5, 0, 0, 0, 2, 0, 9],
    [0, 0, 0, 0, 3, 0, 0, 7, 0]
];

function possible(arr, x, y, num) {
    for (let i = 0; i < 9; i++) {
        if (arr[i][y] === num)
            return false;
    }
    for (let i = 0; i < 9; i++) {
        if (arr[x][i] === num)
            return false;
    }
    var x0 = Math.floor(x / 3) * 3;
    var y0 = Math.floor(y / 3) * 3;
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            if (arr[x0 + i][y0 + j] === num)
                return false;
        }
    }
    return true;
}



function App() {

    const [selected, setSelected] = useState({ row: -1, column: -1 });
    const [puzzle, setPuzzle] = useState(getDeepCopy(grid));
    const numToColor = {
        0: 'rgb(42,42,42)',
        1: 'red',
        2: 'orange',
        3: 'yellow',
        4: 'green',
        5: 'blue',
        6: 'indigo',
        7: 'violet',
        8: 'lightgray',
        9: 'black'
    };

    function getDeepCopy(arr) {
        return JSON.parse(JSON.stringify(arr));
    }

    function handleKeyPress(e) {
        if (selected.row === -1) return;
        if (e.key === '1' || e.key === '2' || e.key === '3' || e.key === '4' || e.key === '5' || e.key === '6' || e.key === '7' || e.key === '8' || e.key === '9') {
            const val = parseInt(e.key);
            var tempGrid = getDeepCopy(puzzle);
            tempGrid[selected.row][selected.column] = val;
            setPuzzle(tempGrid);
        }
    }

    function handleScroll(e, row, column) {
        //console.log("scrolling over " + row + " " + column);
        if (grid[row][column] !== 0) return;

        var tempGrid = getDeepCopy(puzzle);
        const val = tempGrid[row][column];
        if (e.deltaY <= 0) {
            tempGrid[row][column] = (val === 9) ? 0 : val + 1;
        } else {
            tempGrid[row][column] = (val === 0) ? 9 : val - 1;
        }
        setPuzzle(tempGrid);
    }

    function handlePaletteClick(number) {
        //console.log("scrolling over " + row + " " + column);
        if (selected.row === -1) return;

        var tempGrid = getDeepCopy(puzzle);
        tempGrid[selected.row][selected.column] = number;
        setPuzzle(tempGrid);
    }


    function handleCellClick(row, column) {
        //alert("selected: row: " + selected.row + ", column: " + selected.column);
        if (grid[row][column] !== 0) return;
        setSelected({ row: row, column: column });
    }

    return (
        <div className="App" tabIndex={0} onKeyDown={handleKeyPress}>
            <div className="App-header">
                <h3 > Color Sudoku!!!</h3>
                <table className="board">
                    <tbody>
                        {
                            [0, 1, 2, 3, 4, 5, 6, 7, 8].map((row, rIndex) => {
                                return <tr key={rIndex} className={(row + 1) % 3 === 0 ? 'bBorder' : ''} >
                                    {
                                        [0, 1, 2, 3, 4, 5, 6, 7, 8].map((column, cIndex) => {
                                            return <td key={rIndex + cIndex} className={(column + 1) % 3 === 0 ? 'rBorder' : ''} >
                                                <div className="cell" style={{ backgroundColor: numToColor[puzzle[row][column]], borderColor: (selected.row !== row || selected.column !== column) ? 'black' : 'white' }} onClick={() => { handleCellClick(row, column) }} onWheel={(e) => handleScroll(e, row, column)} ></div>
                                            </td>
                                        })
                                    }
                                </tr>
                            })
                        }
                    </tbody>
                </table>

                <h3 > Select a cell above and choose its color below:</h3>
                <table className='palette'>
                    <tbody>
                        <tr>
                            {
                                [0, 1, 2, 3, 4, 5, 6, 7, 8, 9].map((number, numIndex) => {
                                    return <td key={numIndex}>
                                        <div className="cell" style={{ backgroundColor: numToColor[number] }} onClick={() => handlePaletteClick(number)} ></div>
                                    </td>
                                })
                            }
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    );
}

export default App;
