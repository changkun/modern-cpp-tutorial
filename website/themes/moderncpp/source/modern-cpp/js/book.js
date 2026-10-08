// The page script. Everything here is an enhancement: without it the book
// reads in full, every link works, and the outline is a plain list.
(function () {
  var root = document.documentElement;
  var T = root.lang.indexOf('zh') === 0
    ? { copy: '复制', copied: '已复制' }
    : { copy: 'Copy', copied: 'Copied' };

  // The contents drawer on narrow screens.
  var menu = document.querySelector('.menu-btn');
  var sidebar = document.querySelector('.sidebar');
  var scrim = document.querySelector('.scrim');
  function setNav(open) {
    root.classList.toggle('nav-open', open);
    if (menu) menu.setAttribute('aria-expanded', String(open));
  }
  if (menu) menu.addEventListener('click', function () { setNav(!root.classList.contains('nav-open')); });
  if (scrim) scrim.addEventListener('click', function () { setNav(false); });
  if (sidebar) sidebar.addEventListener('click', function (e) { if (e.target.closest('a')) setNav(false); });
  document.addEventListener('keydown', function (e) { if (e.key === 'Escape') setNav(false); });

  // Open the contents with the current chapter in view.
  var current = sidebar && sidebar.querySelector('[aria-current]');
  if (current) sidebar.scrollTop = current.offsetTop - sidebar.clientHeight / 3;

  // The outline marks the section being read: the last heading above a line
  // a quarter of the way down the window, or the last one at the page's end.
  var outline = document.querySelector('.outline');
  var links = [].slice.call(document.querySelectorAll('.outline a'));
  var heads = links.map(function (a) {
    return document.getElementById(decodeURIComponent(a.hash.slice(1)));
  });
  var active = -1;
  var queued = false;
  function mark() {
    queued = false;
    var line = window.innerHeight * 0.25;
    var at = 0;
    for (var i = 0; i < heads.length; i++) {
      if (!heads[i]) continue;
      if (heads[i].getBoundingClientRect().top <= line) at = i;
      else break;
    }
    if (window.innerHeight + window.scrollY >= root.scrollHeight - 4) at = heads.length - 1;
    if (at === active) return;
    if (links[active]) links[active].classList.remove('active');
    links[at].classList.add('active');
    active = at;
    // Keep the marked entry visible when the outline itself scrolls.
    var a = links[at];
    if (a.offsetTop < outline.scrollTop + 40 || a.offsetTop > outline.scrollTop + outline.clientHeight - 40) {
      outline.scrollTop = a.offsetTop - outline.clientHeight / 3;
    }
  }
  if (links.length) {
    window.addEventListener('scroll', function () {
      if (!queued) { queued = true; requestAnimationFrame(mark); }
    }, { passive: true });
    window.addEventListener('resize', mark);
    mark();
  }

  // A copy button on every code block.
  [].forEach.call(document.querySelectorAll('.code'), function (box) {
    var pre = box.querySelector('pre');
    if (!pre || !navigator.clipboard) return;
    var btn = document.createElement('button');
    btn.type = 'button';
    btn.className = 'copy-btn';
    btn.textContent = T.copy;
    var timer = 0;
    btn.addEventListener('click', function () {
      navigator.clipboard.writeText(pre.innerText.replace(/\n$/, '')).then(function () {
        btn.textContent = T.copied;
        btn.classList.add('done');
        clearTimeout(timer);
        timer = setTimeout(function () {
          btn.textContent = T.copy;
          btn.classList.remove('done');
        }, 1600);
      }, function () {});
    });
    box.appendChild(btn);
  });
})();
