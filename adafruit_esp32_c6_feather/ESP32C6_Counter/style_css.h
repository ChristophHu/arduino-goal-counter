const char STYLE_CSS[] PROGMEM = R"rawliteral(
/* style.css */
* {
    -webkit-user-select: none
    -khtml-user-select: none
    -moz-user-select: none
    -ms-user-select: none
    user-select: none
}
*,
*::before,
*::after {
    box-sizing: border-box;
}
button,
input,
optgroup,
select,
textarea {
    font-family: inherit; /* 1 */
    font-size: 100%; /* 1 */
    line-height: 1.15; /* 1 */
    margin: 0; /* 2 */
}
button,
select { /* 1 */
    text-transform: none;
}
button {
    background-color: transparent;
    background-image: none;
}
button,
[role="button"] {
    cursor: pointer;
}
button,
input,
optgroup,
select,
textarea {
    padding: 0;
    line-height: inherit;
    color: inherit;
}
.scrollbar-hide {
    -ms-overflow-style: none;
    scrollbar-width: none;
    overflow-y: scroll;
    &::-webkit-scrollbar {
        display: none;
        width: 0;
        height: 0;
    }
}
body {
    background: #121212;
}

.bg-black {
  --tw-bg-opacity: 1;
  background-color: rgba(0, 0, 0, var(--tw-bg-opacity));
}
.bg-blue-500 {
  --tw-bg-opacity: 1;
  background-color: rgba(59, 130, 246, var(--tw-bg-opacity));
}
.hover\:bg-blue-600:hover {
    --tw-bg-opacity: 1;
    background-color: rgba(37, 99, 235, var(--tw-bg-opacity));
}
.bg-gray-900 {
    --tw-bg-opacity: 1;
    background-color: rgba(30, 30, 30, var(--tw-bg-opacity));
}
.bg-red-500 {
    --tw-bg-opacity: 1;
    background-color: rgba(239, 68, 68, var(--tw-bg-opacity));
}
.hover\:bg-red-600:hover {
    --tw-bg-opacity: 1;
    background-color: rgba(220, 38, 38, var(--tw-bg-opacity));
}
.border-none {
  border-style: none;
}
.container {
  width: 100%;
}
@media (min-width: 640px) {
  .container {
    max-width: 640px;
  }
}
@media (min-width: 768px) {
  .container {
    max-width: 768px;
  }
}
@media (min-width: 1024px) {
  .container {
    max-width: 1024px;
  }
}
@media (min-width: 1280px) {
  .container {
    max-width: 1280px;
  }
}
@media (min-width: 1536px) {
  .container {
    max-width: 1536px;
  }
}
.cursor-pointer {
  cursor: pointer;
}
.flex {
  display: flex;
}
.flex-col {
  flex-direction: column;
}
.flex-row {
  flex-direction: row;
}
.font-sans {
    font-family: ui-sans-serif, system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, "Noto Sans", sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji";
}
.h-6 {
  height: 1.5rem;
}
.items-center {
  align-items: center;
}
.justify-center {
  justify-content: center;
}
m-0 {
    margin: 0px;
}
.min-h-screen {
    min-height: 100vh;
}
.ml-2 {
  margin-left: 0.5rem;
}
.mr-2 {
  margin-right: 0.5rem;
}
.mt-2 {
  margin-top: 0.5rem;
}
.mx-auto {
  margin-left: auto;
  margin-right: auto;
}
.p-2 {
  padding: 0.5rem;
}
.rounded {
  border-radius: 0.25rem;
}
.rounded-lg {
  border-radius: 0.5rem;
}
.sr-only {
  position: absolute;
  width: 1px;
  height: 1px;
  padding: 0;
  margin: -1px;
  overflow: hidden;
  clip: rect(0, 0, 0, 0);
  white-space: nowrap;
  border-width: 0;
}
.stroke-2 {
    stroke-width: 2;
}
.text-center {
    text-align: center;
}
.text-white {
  --tw-text-opacity: 1;
  color: rgba(255, 255, 255, var(--tw-text-opacity));
}
.w-96 {
  width: 24rem;
}
.w-6 {
  width: 1.5rem;
}
.md\:w-96 {
    width: 24rem;
}
.w-full {
  width: 100%;
}
.sm\:w-full {
    width: 100%;
}
)rawliteral";