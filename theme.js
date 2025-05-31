const themeToggle = document.getElementById('theme-toggle');

function setThemeIcon(isDark) {
  themeToggle.textContent = isDark ? "🌜" : "🌞";
}

// Apply saved or system theme on load
let theme = localStorage.getItem('theme');
if (!theme) {
  theme = window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
}
const isDark = theme === 'dark';
document.body.classList.toggle('dark', isDark);
setThemeIcon(isDark);

// Toggle theme and update icon/persistence
themeToggle.addEventListener('click', () => {
  const isNowDark = !document.body.classList.contains('dark');
  document.body.classList.toggle('dark', isNowDark);
  setThemeIcon(isNowDark);
  localStorage.setItem('theme', isNowDark ? 'dark' : 'light');
});
