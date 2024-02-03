// preload.js
console.log('preload script loaded');
const { contextBridge } = require('electron');
//const path = require('path');
const marked = require('marked');

contextBridge.exposeInMainWorld('marked', marked);
//contextBridge.exposeInMainWorld('appDir', path.resolve(__dirname));
