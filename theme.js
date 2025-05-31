const themeToggle = document.getElementById('theme-toggle');

// Check for saved preference
let theme = localStorage.getItem('theme');
if (!theme) {
  // If no saved theme, check system preference
  theme = window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
}
document.body.classList.toggle('dark', theme === 'dark');

// Toggle theme and save preference
themeToggle.addEventListener('click', () => {
  document.body.classList.toggle('dark');
  const isDark = document.body.classList.contains('dark');
  localStorage.setItem('theme', isDark ? 'dark' : 'light');
});

