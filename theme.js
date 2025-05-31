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

// Highlight current page in nav bar
document.querySelectorAll('nav .nav-link').forEach(link => {
  const linkHref = link.getAttribute('href').replace(/[#?].*$/, '');
  // Get the current file from location.pathname
  const currentPage = location.pathname.split('/').pop() || "index.html";
  // If root or index.html
  if ((linkHref === "index.html" && (currentPage === "" || currentPage === "index.html")) ||
      (linkHref !== "" && linkHref === currentPage)) {
    link.classList.add('active');
  }
});


