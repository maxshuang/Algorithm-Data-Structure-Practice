// preload.js
console.log('preload script loaded');
const { contextBridge, ipcRenderer } = require('electron');
const marked = require('marked');

contextBridge.exposeInMainWorld('marked', marked);

// register an object to render process
contextBridge.exposeInMainWorld('electron', {
    // send event to main process
    openFileDialog: () => ipcRenderer.send('open-file-dialog'),
    // receive event from main process
    onFileSelected: (func) => {
      ipcRenderer.on('file-selected', (event, result) => func(result))
    }
});