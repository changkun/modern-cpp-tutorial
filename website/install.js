var fs = require('fs')
var execSync = require('child_process').execSync
var deps = require('./package.json').dependencies
var depFolders = Object.keys(deps)

for (var depFolder in deps) {
  if (!fs.existsSync('./node_modules/' + depFolder)) {
    console.log('Dependency "' + depFolder + '" is NOT installed - installing now...')
    execSync('npm install')
    process.exit(0)
  }
}

console.log('All dependencies are already installed.')
