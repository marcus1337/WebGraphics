
var onModuleInit = function (text) {
  if (text == '')
    onModuleCreated();
  else
    console.log(text); //log errors
};

var Module = {
  canvas: document.getElementById("canvas"),
  setStatus: onModuleInit
};

function resize() {
  const width = window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth;
  const height = window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight;
  Module.resizeWindow(width - 1, height);
}
document.getElementsByTagName("body")[0].onresize = resize;

function onModuleCreated() {  
  resize();
}

document.addEventListener("fullscreenchange", function () {
  resize();
});