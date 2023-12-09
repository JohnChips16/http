const { exec } = require('child_process');
const path = require('path');

const startHttpServer = (port) => {
  // Specify the full path to your shell script
  const scriptPath = path.resolve(__dirname, '../lib/c++/BuildNrun.sh');
  const command = `${scriptPath} ${port}`;

  const childProcess = exec(command, (error, stdout, stderr) => {
    if (error) {
      console.error(`Error executing script: ${error}`);
      return;
    }

    console.log(`Script output:\n${stdout}`);
    console.error(`Script errors:\n${stderr}`);
  });

  childProcess.on('exit', (code) => {
    console.log(`Script exited with code ${code}`);
  });
};

// Example: Run the script with PORT 8080
// const PORT = 8080;
// startHttpServer(PORT);

module.exports = startHttpServer
