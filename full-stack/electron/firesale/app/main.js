const { app, BrowserWindow } = require('electron');
const path = require('path');

let mainWindow = null;

//console.log(path.join(__dirname, 'preload.js'));
app.on('ready', () => {
  mainWindow = new BrowserWindow({ 
    show: false,
    webPreferences: { 
      devTools: true,
      // Electron v20 changes the default setting for sandboxing renderers with preload scripts to true
      sandbox: false,
      // for electron 20.x.x, need preload to bridge the usage
      // of package like "marked"
      preload: path.join(__dirname, 'preload.js')
      //preload: "app/preload.js"
    }
  });

  mainWindow.loadFile('app/index.html');

  // Open the DevTools.
  mainWindow.webContents.openDevTools();

  mainWindow.webContents.on('did-fail-load', (event, errorCode, errorDescription) => {
    console.log(`An error occurred: ${errorDescription}`)
  })

  mainWindow.webContents.on('did-finish-load', (event, errorCode, errorDescription) => {
    console.log(`finish load: ${event}`)
  })
   
  mainWindow.once('ready-to-show', () => {
    console.log('ready-to-show event fired.');
    mainWindow.show();
  });

  mainWindow.on('closed', () => {
    console.log('closed event fired.');
    mainWindow = null;
  });
});
