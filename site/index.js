function onPageLoad() {
  console.log('Here');

  document.getElementById('year').innerHTML = new Date().getFullYear();
}