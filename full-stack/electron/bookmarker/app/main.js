const { app, BrowserWindow } = require('electron');

let mainWindow = null;

app.on('ready', () => {
    console.log('Hello from Electron.');
    mainWindow = new BrowserWindow({
        webPreferences: { devTools: true}
    });
    mainWindow.webContents.loadFile('app/index.html');

    mainWindow.webContents.on('did-finish-load', (event, errorCode, errorDescription) => {
      console.log(`finish load: ${event}`)
    })
});