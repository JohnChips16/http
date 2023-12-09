const startHttpServer = require('../module/module.exports.js')
const express = require('express')
const app = express()

startHttpServer(8000)

app.get('/express/test', (req, res) => {
  try {
    res.status(200).send('Server OK!');
  } catch (err) {
    console.log(err);
    res.status(500).send('Internal server error!');
  }
});