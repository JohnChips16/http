const assert = require('assert');
const startHttpServer = require('../module/module.exports.js');

describe('HTTP Server Runner', () => {
  it('should execute the script with the given port', (done) => {
    // Mock the exec function to simulate script execution
    const originalExec = require('child_process').exec;
    require('child_process').exec = (command, callback) => {
      assert.strictEqual(command, '../lib/c++/BuildNrun.sh 8080');
      callback(null, 'Mocked output', 'Mocked errors');
    };

    // Run the function
    startHttpServer(8080);

    // Restore the original exec function
    require('child_process').exec = originalExec;

    done();
  });

  // Add more tests as needed
});
