const { app, BrowserWindow, dialog, ipcMain } = require('electron');
const path = require('path');
const fs = require('fs');

let mainWindow = null;

//console.log(path.join(__dirname, 'preload.js'));
app.on('ready', () => {
  // mainWindow is another process, all methods calls are remote calls
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

  const getFileFromUser = (event) => {
    const files = dialog.showOpenDialog(mainWindow, {
      properties: ['openFile'],
      filters: [
        { name: 'Text Files', extensions: ['txt'] },
        { name: 'Markdown Files', extensions: ['md', 'markdown'] }
      ]
    }).then(result => {
      if (!result.canceled) {
        const filePath = result.filePaths[0];
        openFile(filePath, event);
      }
    }).catch(err => {
      console.log(err);
    });
  };

  const openFile = (file, event) => {
    fs.readFile(file, 'utf-8', (err, data) => {
      if (err) {
        event.reply('file-selected', { error: err.message });
      } else {
        // how to return file name
        event.reply('file-selected', { file: file, content: data });
      }
    });
  };

  ipcMain.on('open-file-dialog', getFileFromUser);
});