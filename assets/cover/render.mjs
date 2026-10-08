// The cover, computed rather than drawn: C++ as the rings of a tree. A faint
// core of yearly rings is C++98/03, the language the book assumes; outside it,
// one ring for every year from 2011 to 2026. The six years that brought a
// standard are drawn stronger and carry a dot for each feature that the
// book's Feature Index (book/*/appendix3.md) lists under that standard. The
// outermost, C++26, is still an outlook: dashed, in gold.
//
// The words are HTML laid over the art, set in the site's faces, and the page
// is photographed by a headless Chromium. It writes, for both editions:
//
//   assets/cover-{en,zh}.png                         full size, for README, PDF, EPUB
//   website/src/modern-cpp/assets/cover-{en,zh}-web.jpg     the landing page
//   website/src/modern-cpp/assets/cover-{en,zh}-logo.png    the top bar
//   website/src/modern-cpp/assets/og-{en,zh}.png            link previews
//   website/src/modern-cpp/assets/{favicon,apple-touch-icon}.png  the icon
//
// Run from the repository root with playwright-core available:
//
//   npm i --no-save playwright-core && npx playwright-core install chromium
//   node assets/cover/render.mjs
//
// (PLAYWRIGHT_CORE=/path/to/playwright-core/index.mjs points at another copy.)

import { mkdirSync } from 'node:fs';
import { dirname, join } from 'node:path';
import { fileURLToPath } from 'node:url';

const ROOT = join(dirname(fileURLToPath(import.meta.url)), '..', '..');
const SITE_ASSETS = join(ROOT, 'website', 'src', 'modern-cpp', 'assets');
const { chromium } = await import(process.env.PLAYWRIGHT_CORE || 'playwright-core');

// Features per standard, one entry each, as appendix 3 lists them. Its table
// folds C++14 into C++11; the rows it marks "(C++14)" are split out here.
const STANDARDS = [
  { year: 2011, name: 'C++11', features: [
    'nullptr', 'constexpr', 'initializer_list', 'auto', 'decltype', 'trailing return type', 'range-based for',
    'extern templates', 'alias templates', 'default template arguments', 'variadic templates',
    'delegating constructors', 'inheriting constructors', 'override', 'final', '= default', '= delete',
    'enum class', 'SFINAE / enable_if', 'lambda expressions', 'std::function', 'std::bind',
    'rvalue references', 'move semantics', 'perfect forwarding', 'std::array', 'std::forward_list',
    'unordered containers', 'std::tuple', 'shared_ptr', 'unique_ptr', 'weak_ptr', 'std::regex',
    'std::thread', 'mutexes', 'futures', 'condition variables', 'atomics and the memory model',
    'long long', 'noexcept', 'raw string literals', 'user-defined literals', 'alignment'] },
  { year: 2014, name: 'C++14', features: ['relaxed constexpr', 'decltype(auto)', 'generic lambdas', 'make_unique'] },
  { year: 2017, name: 'C++17', features: [
    'structured bindings', 'if init-statement', 'switch init-statement', 'if constexpr', 'fold expressions',
    'auto non-type template parameters', 'inline variables', 'nested namespaces', 'constexpr lambda',
    'single-argument static_assert', 'aggregate rules', 'logical metafunctions', '__has_include',
    'guaranteed copy elision', 'string_view', 'std::byte', 'try_emplace / merge', 'std::pmr',
    'std::filesystem', 'over-aligned new', 'special math functions'] },
  { year: 2020, name: 'C++20', features: ['concepts', 'modules', 'ranges', 'coroutines', 'bit_cast'] },
  { year: 2023, name: 'C++23', features: [
    'deducing this', 'if consteval', 'multidimensional subscript', 'auto(x)', 'static operator()', '[[assume]]',
    'std::expected', 'std::print', 'std::mdspan', 'std::flat_map', 'std::flat_set', 'views::zip',
    'string::contains', 'std::byteswap'] },
  { year: 2026, name: 'C++26', outlook: true, features: [
    'static reflection', 'contracts', 'pack indexing', '= delete("reason")', 'placeholder _',
    'std::execution', 'saturation arithmetic'] },
];

const TEXT = {
  en: { lang: 'en', author: 'Changkun Ou', edition: 'Third Edition', title: 'Modern C++<br>Tutorial', sub: 'C++11 to C++26 On the Fly', url: 'changkun.de/modern-cpp' },
  zh: { lang: 'zh-CN', author: '欧长坤 著', edition: '第三版', title: '现代 C++<br>教程', sub: '高速上手 C++11 到 C++26', url: 'changkun.de/modern-cpp' },
};

// The cover is 823 × 1079 CSS pixels, the old cover's proportions; ×3 gives
// the 2469 × 3237 image the PDF and EPUB builds already expect.
const W = 823, H = 1079;
const CX = 150, BASE = H - 84; // the rings' centre, on the baseline
const CREAM = '#f6ece0', GOLD = '#e7b45e';
const radius = (year) => (year < 2011 ? 20 + (year - 1998) * 10 : 150 + (year - 2011) * 28);

function art() {
  const f = (n) => n.toFixed(1);
  const ring = (r) => `M${f(CX + r)},${BASE}A${r},${r} 0 0 0 ${f(CX - r)},${BASE}`;
  const stds = new Map(STANDARDS.map((s) => [s.year, s]));
  let rings = '', dots = '', labels = '';
  for (let y = 1998; y <= 2026; y++) {
    const r = radius(y), s = stds.get(y);
    if (!s) {
      rings += `<path d="${ring(r)}" stroke-opacity="${y < 2011 ? 0.11 : 0.07}"/>`;
      continue;
    }
    rings += s.outlook
      ? `<path d="${ring(r)}" stroke="${GOLD}" stroke-opacity="0.85" stroke-width="1.4" stroke-dasharray="2 6" stroke-linecap="round"/>`
      : `<path d="${ring(r)}" stroke-opacity="0.34" stroke-width="1.2"/>`;
    // Dots fill the part of the ring inside the cover, evenly, from the
    // baseline round towards the left edge.
    const far = Math.acos(Math.max(-1, (24 - CX) / r)) * 180 / Math.PI;
    const a0 = 5, a1 = Math.min(far, 176) - 3, n = s.features.length;
    for (let k = 0; k < n; k++) {
      const a = (a0 + ((k + 0.5) * (a1 - a0)) / n) * Math.PI / 180;
      const x = CX + r * Math.cos(a), yy = BASE - r * Math.sin(a);
      dots += s.outlook
        ? `<circle cx="${f(x)}" cy="${f(yy)}" r="4.2" fill="none" stroke="${GOLD}" stroke-width="1.6"><title>${s.features[k]}</title></circle>`
        : `<circle cx="${f(x)}" cy="${f(yy)}" r="3.4" fill="${CREAM}"><title>${s.features[k]}</title></circle>`;
    }
    labels += `<text x="${f(CX + r)}" y="${BASE + 26}"${s.outlook ? ` fill="${GOLD}" fill-opacity="1"` : ''}>${s.name}</text>`;
  }
  labels += `<text x="${CX}" y="${BASE + 26}" fill-opacity="0.38">C++98</text>`;
  return `<svg class="art" viewBox="0 0 ${W} ${H}" xmlns="http://www.w3.org/2000/svg">
  <g fill="none" stroke="${CREAM}" stroke-width="1">${rings}</g>
  <line x1="0" x2="${W}" y1="${BASE}" y2="${BASE}" stroke="${CREAM}" stroke-opacity="0.3"/>
  <g>${dots}</g>
  <g font-family="JetBrains Mono, monospace" font-size="12.5" font-weight="500" text-anchor="middle" fill="${CREAM}" fill-opacity="0.62">${labels}</g>
</svg>`;
}

const FONTS = `<link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;600&family=JetBrains+Mono:wght@500&family=Source+Serif+4:opsz,wght@8..60,600&family=Noto+Serif+SC:wght@600&display=block">`;
const FIELD = `background:
    radial-gradient(620px 520px at ${CX}px ${BASE}px, rgba(255, 214, 196, 0.10), transparent 70%),
    linear-gradient(172deg, #8a323d 0%, #74272f 42%, #521a22 100%);`;

function coverPage(t) {
  return `<!doctype html><html lang="${t.lang}"><head><meta charset="utf-8">${FONTS}<style>
  html, body { margin: 0; }
  .cover { position: relative; width: ${W}px; height: ${H}px; overflow: hidden; ${FIELD} color: ${CREAM}; font-family: Inter, "PingFang SC", sans-serif; }
  .art { position: absolute; inset: 0; width: 100%; height: 100%; }
  .head { position: absolute; top: 60px; left: 64px; right: 64px; display: flex; justify-content: space-between;
    font-size: 13px; font-weight: 600; letter-spacing: 0.22em; text-transform: uppercase; }
  .author { opacity: 0.74; }
  .edition { color: ${GOLD}; }
  h1 { position: absolute; top: 118px; left: 60px; margin: 0;
    font: 600 92px/1.0 "Source Serif 4", "Noto Serif SC", serif; letter-spacing: -0.02em; }
  .sub { position: absolute; top: 330px; left: 64px; margin: 0; font-size: 25px; font-weight: 400; opacity: 0.86; letter-spacing: -0.005em; }
  :lang(zh-CN) .head { letter-spacing: 0.12em; }
  :lang(zh-CN) h1 { font-size: 96px; line-height: 1.12; letter-spacing: 0.01em; }
  :lang(zh-CN) .sub { top: 362px; }
  .art text { font-variant-ligatures: none; }
</style></head><body><div class="cover">
  ${art()}
  <div class="head"><span class="author">${t.author}</span><span class="edition">${t.edition}</span></div>
  <h1>${t.title}</h1>
  <p class="sub">${t.sub}</p>
</div></body></html>`;
}

// A link preview: the cover beside the title, 1200 × 630.
function ogPage(t, coverUrl) {
  return `<!doctype html><html lang="${t.lang}"><head><meta charset="utf-8">${FONTS}<style>
  html, body { margin: 0; }
  .card { width: 1200px; height: 630px; display: flex; align-items: center; gap: 72px; padding: 0 96px; box-sizing: border-box;
    background: radial-gradient(900px 600px at 20% 30%, #7a2a34, #4a161d 75%); color: ${CREAM}; font-family: Inter, "PingFang SC", sans-serif; }
  img { width: 330px; height: auto; border-radius: 4px; box-shadow: 0 0 0 1px rgba(255,255,255,0.06), 0 30px 60px -10px rgba(0,0,0,0.55); }
  h1 { margin: 0; font: 600 76px/1.02 "Source Serif 4", "Noto Serif SC", serif; letter-spacing: -0.02em; }
  .sub { margin: 22px 0 0; font-size: 30px; opacity: 0.86; }
  .meta { margin: 46px 0 0; font-size: 17px; font-weight: 600; letter-spacing: 0.2em; text-transform: uppercase; }
  .meta span { color: ${GOLD}; }
  .url { margin: 10px 0 0; font-size: 22px; opacity: 0.6; }
  :lang(zh-CN) h1 { font-size: 80px; line-height: 1.12; letter-spacing: 0.01em; }
  :lang(zh-CN) .meta { letter-spacing: 0.12em; }
</style></head><body><div class="card">
  <img src="${coverUrl}" alt="">
  <div><h1>${t.title}</h1><p class="sub">${t.sub}</p><p class="meta">${t.author} · <span>${t.edition}</span></p><p class="url">${t.url}</p></div>
</div></body></html>`;
}

// The icon: the cover's field and rings behind a serif "C++".
function iconPage() {
  const rings = [44, 70, 96, 122, 148].map((r, i) =>
    `<path d="M${18 + r},180A${r},${r} 0 0 0 ${18 - r},180" stroke="${i === 4 ? GOLD : CREAM}" stroke-opacity="${i === 4 ? 0.9 : 0.3}" stroke-width="3"${i === 4 ? ' stroke-dasharray="3 9" stroke-linecap="round"' : ''}/>`).join('');
  return `<!doctype html><html><head><meta charset="utf-8">${FONTS}<style>
  html, body { margin: 0; }
  .icon { position: relative; width: 180px; height: 180px; overflow: hidden; ${FIELD.replace(`${CX}px ${BASE}px`, '18px 180px')} }
  svg { position: absolute; inset: 0; }
  b { position: absolute; inset: 0; display: grid; place-items: center; padding-bottom: 8px;
    font: 600 76px/1 "Source Serif 4", serif; letter-spacing: -0.03em; color: ${CREAM}; }
</style></head><body><div class="icon">
  <svg viewBox="0 0 180 180" width="180" height="180" fill="none">${rings}</svg><b>C++</b>
</div></body></html>`;
}

const browser = await chromium.launch();
async function shoot(html, { width, height, scale, out, type = 'png', quality }) {
  const page = await browser.newPage({ viewport: { width, height }, deviceScaleFactor: scale });
  await page.setContent(html, { waitUntil: 'networkidle' });
  await page.evaluate(() => document.fonts.ready);
  mkdirSync(dirname(out), { recursive: true });
  await page.screenshot({ path: out, type, quality, clip: { x: 0, y: 0, width, height } });
  await page.close();
  console.log('wrote', out.replace(ROOT + '/', ''));
}

for (const ed of ['en', 'zh']) {
  const html = coverPage(TEXT[ed]);
  const full = join(ROOT, 'assets', `cover-${ed}.png`);
  await shoot(html, { width: W, height: H, scale: 3, out: full });
  await shoot(html, { width: W, height: H, scale: 720 / W, out: join(SITE_ASSETS, `cover-${ed}-web.jpg`), type: 'jpeg', quality: 88 });
  await shoot(html, { width: W, height: H, scale: 100 / W, out: join(SITE_ASSETS, `cover-${ed}-logo.png`) });
  const web = 'data:image/jpeg;base64,' + (await import('node:fs')).readFileSync(join(SITE_ASSETS, `cover-${ed}-web.jpg`)).toString('base64');
  await shoot(ogPage(TEXT[ed], web), { width: 1200, height: 630, scale: 1, out: join(SITE_ASSETS, `og-${ed}.png`) });
}
await shoot(iconPage(), { width: 180, height: 180, scale: 1, out: join(SITE_ASSETS, 'apple-touch-icon.png') });
await shoot(iconPage(), { width: 180, height: 180, scale: 32 / 180, out: join(SITE_ASSETS, 'favicon.png') });
await browser.close();
