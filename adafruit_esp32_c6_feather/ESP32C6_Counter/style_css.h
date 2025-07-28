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

.absolute {
  position: absolute;
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
.left-0 {
  left: 0;
}
.list-style-none {
  list-style: none;
}
.m-0 {
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
.overflow-hidden {
  overflow: hidden;
}
.p-2 {
  padding: 0.5rem;
}
.pointer-events-none {
  pointer-events: none;
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
.z-10 {
  z-index: 10;
}
.z-20 {
  z-index: 20;
}
.z-30 {
  z-index: 30;
}
.z-40 {
  z-index: 40;
}

:root {
  --main-width: 12rem;
  --main-height: 12rem;
  --font-size: 10rem;
  --line-height: 10.6rem;
}
* {
  margin: 0;
  padding: 0;
}

/* HTML,
BODY {
  width: 100%;
  height: 100%;
} */
/* body {
  color: #000;
  background: #37383d;
  font-family: Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
} */
/* #flipclock ul {
  list-style: none;
}
#flipclock {
  pointer-events: none;
} */
/* .flip-pane {
  position: absolute;
  left: 50%;
  top: 50%;
} */
/* .flip-pane-left {
  width: 808px;
  height: 344px;
  margin: -192px 0 0 -476px;
  z-index: 1;
} */
.flip-pane-2 {
  width: 100%;
  height: var(--main-height); /* 146px */
  display: flex;
  flex-direction: row;
  justify-content: center;
}
.flip-item {
  position: relative;
  float: left;
}
.flip-pane-2 .flip {
  width: var(--main-width);
  height: var(--main-height);
}
.flip li {
  z-index: 1;
  position: absolute;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
}
.flip li:first-child {
  z-index: 2;
}
.flip li span {
  display: block;
  height: 100%;
  -webkit-perspective: 900px;
  -moz-perspective: 900px;
  -ms-perspective: 900px;
  perspective: 900px;
}
.vs-icon {
  display: flex;
  position: relative;
  top: calc(var(--main-height) / 4 + 20px);
  color: #b7b7b7;
  align-items: center;
}
.flip-pane-2 div {
  height: calc((var(--main-height) / 2) - 1px); /*72px; */
}
.flip-pane .flip-shadow {
  position: absolute;
  width: 100%;
  height: 100%;
  z-index: 2;
}
.flip-up {
  -webkit-transform-origin: 50% 100%;
  -moz-transform-origin: 50% 100%;
  -o-transform-origin: 50% 100%;
  -ms-transform-origin: 50% 100%;
  transform-origin: 50% 100%;
  -webkit-backface-visibility: hidden;
  -moz-backface-visibility: hidden;
  -ms-backface-visibility: hidden;
  backface-visibility: hidden;
  top: 0;
}
.flip-down {
  -webkit-transform-origin: 50% 0%;
  -moz-transform-origin: 50% 0%;
  -o-transform-origin: 50% 0%;
  -ms-transform-origin: 50% 0%;
  transform-origin: 50% 0%;
  -webkit-backface-visibility: hidden;
  -moz-backface-visibility: hidden;
  -ms-backface-visibility: hidden;
  backface-visibility: hidden;
  bottom: 0;
}
.flip-pane-2 .flip-text {
  position: absolute;
  left: 0;
  z-index: 1;
  width: 100%;
  height: 200%;
  font-weight: 700;
  color: #b7b7b7;
  text-align: center;
  -webkit-border-radius: 16px;
  border-radius: 16px;
}
.flip-pane-2 .flip-text {
  font-size: var(--font-size); /* 160px; */
  line-height: var(--line-height); /* 147px; */
  background: #121212; /* #000; */
}
.flip-up .flip-text {
  top: 0;
}
.flip-down .flip-text {
  bottom: 0;
}
#flipcounter .before {
  z-index: 3;
}
#flipcounter .active {
  -webkit-animation: flip-ani-index 0.5s 0.5s linear both;
  -moz-animation: flip-ani-index 0.5s 0.5s linear both;
  -o-animation: flip-ani-index 0.5s 0.5s linear both;
  -ms-animation: flip-ani-index 0.5s 0.5s linear both;
  animation: flip-ani-index 0.5s 0.5s linear both;
  z-index: 2;
}
#flipcounter .active .flip-down {
  z-index: 2;
  -webkit-animation: flip-ani-up 0.5s 0.5s linear both;
  -moz-animation: flip-ani-up 0.5s 0.5s linear both;
  -o-animation: flip-ani-up 0.5s 0.5s linear both;
  -ms-animation: flip-ani-up 0.5s 0.5s linear both;
  animation: flip-ani-up 0.5s 0.5s linear both;
}
#flipcounter .before .flip-up {
  z-index: 2;
  -webkit-animation: flip-ani-down 0.5s cubic-bezier(0.47, 0, 0.745, 0.715) both;
  -moz-animation: flip-ani-down 0.5s cubic-bezier(0.47, 0, 0.745, 0.715) both;
  -o-animation: flip-ani-down 0.5s cubic-bezier(0.47, 0, 0.745, 0.715) both;
  -ms-animation: flip-ani-down 0.5s cubic-bezier(0.47, 0, 0.745, 0.715) both;
  animation: flip-ani-down 0.5s cubic-bezier(0.47, 0, 0.745, 0.715) both;
}
#flipcounter .before .flip-up .flip-shadow {
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0, rgba(0,0,0,0)), color-stop(1, #000));
  background: -webkit-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -moz-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -o-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -ms-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  -webkit-animation: show 0.5s linear both;
  -moz-animation: show 0.5s linear both;
  -o-animation: show 0.5s linear both;
  -ms-animation: show 0.5s linear both;
  animation: show 0.5s linear both;
}
#flipcounter .before .flip-down .flip-shadow {
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0, #000), color-stop(1, rgba(0,0,0,0)));
  background: -webkit-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -moz-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -o-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -ms-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  -webkit-animation: show 0.5s linear both;
  -moz-animation: show 0.5s linear both;
  -o-animation: show 0.5s linear both;
  -ms-animation: show 0.5s linear both;
  animation: show 0.5s linear both;
}
#flipcounter .active .flip-up .flip-shadow {
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0, rgba(0,0,0,0)), color-stop(1, #000));
  background: -webkit-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -moz-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -o-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: -ms-linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  background: linear-gradient(top, rgba(0,0,0,0) 0%, #000 100%);
  -webkit-animation: hide 0.5s 0.3s linear both;
  -moz-animation: hide 0.5s 0.3s linear both;
  -o-animation: hide 0.5s 0.3s linear both;
  -ms-animation: hide 0.5s 0.3s linear both;
  animation: hide 0.5s 0.3s linear both;
}
#flipcounter .active .flip-down .flip-shadow {
  background: -webkit-gradient(linear, left top, left bottom, color-stop(0, #000), color-stop(1, rgba(0,0,0,0)));
  background: -webkit-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -moz-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -o-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: -ms-linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  background: linear-gradient(top, #000 0%, rgba(0,0,0,0) 100%);
  -webkit-animation: hide 0.5s 0.3s linear both;
  -moz-animation: hide 0.5s 0.3s linear both;
  -o-animation: hide 0.5s 0.3s linear both;
  -ms-animation: hide 0.5s 0.3s linear both;
  animation: hide 0.5s 0.3s linear both;
}
@-moz-keyframes flip-ani-index {
  0% {
    z-index: 2;
  }

  5% {
    z-index: 4;
  }

  100% {
    z-index: 4;
  }
}
@-webkit-keyframes flip-ani-index {
  0% {
    z-index: 2;
  }

  5% {
    z-index: 4;
  }

  100% {
    z-index: 4;
  }
}
@-o-keyframes flip-ani-index {
  0% {
    z-index: 2;
  }

  5% {
    z-index: 4;
  }

  100% {
    z-index: 4;
  }
}
@-ms-keyframes flip-ani-index {
  0% {
    z-index: 2;
  }

  5% {
    z-index: 4;
  }

  100% {
    z-index: 4;
  }
}
@keyframes flip-ani-index {
  0% {
    z-index: 2;
  }

  5% {
    z-index: 4;
  }

  100% {
    z-index: 4;
  }
}
@-moz-keyframes flip-ani-up {
  0% {
    -webkit-transform: rotateX(90deg);
    -moz-transform: rotateX(90deg);
    -o-transform: rotateX(90deg);
    -ms-transform: rotateX(90deg);
    transform: rotateX(90deg);
  }

  60% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }

  100% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }
}
@-webkit-keyframes flip-ani-up {
  0% {
    -webkit-transform: rotateX(90deg);
    -moz-transform: rotateX(90deg);
    -o-transform: rotateX(90deg);
    -ms-transform: rotateX(90deg);
    transform: rotateX(90deg);
  }

  60% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }

  100% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }
}
@-o-keyframes flip-ani-up {
  0% {
    -webkit-transform: rotateX(90deg);
    -moz-transform: rotateX(90deg);
    -o-transform: rotateX(90deg);
    -ms-transform: rotateX(90deg);
    transform: rotateX(90deg);
  }

  60% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }

  100% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }
}
@-ms-keyframes flip-ani-up {
  0% {
    -webkit-transform: rotateX(90deg);
    -moz-transform: rotateX(90deg);
    -o-transform: rotateX(90deg);
    -ms-transform: rotateX(90deg);
    transform: rotateX(90deg);
  }

  60% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }

  100% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }
}
@keyframes flip-ani-up {
  0% {
    -webkit-transform: rotateX(90deg);
    -moz-transform: rotateX(90deg);
    -o-transform: rotateX(90deg);
    -ms-transform: rotateX(90deg);
    transform: rotateX(90deg);
  }

  60% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }

  100% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
  }
}
@-moz-keyframes flip-ani-down {
  0% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  99% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
    -webkit-transform: rotateX(-90deg);
    -moz-transform: rotateX(-90deg);
    -o-transform: rotateX(-90deg);
    -ms-transform: rotateX(-90deg);
    transform: rotateX(-90deg);
  }
}
@-webkit-keyframes flip-ani-down {
  0% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  99% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
    -webkit-transform: rotateX(-90deg);
    -moz-transform: rotateX(-90deg);
    -o-transform: rotateX(-90deg);
    -ms-transform: rotateX(-90deg);
    transform: rotateX(-90deg);
  }
}
@-o-keyframes flip-ani-down {
  0% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  99% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
    -webkit-transform: rotateX(-90deg);
    -moz-transform: rotateX(-90deg);
    -o-transform: rotateX(-90deg);
    -ms-transform: rotateX(-90deg);
    transform: rotateX(-90deg);
  }
}
@-ms-keyframes flip-ani-down {
  0% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  99% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
    -webkit-transform: rotateX(-90deg);
    -moz-transform: rotateX(-90deg);
    -o-transform: rotateX(-90deg);
    -ms-transform: rotateX(-90deg);
    transform: rotateX(-90deg);
  }
}
@keyframes flip-ani-down {
  0% {
    -webkit-transform: rotateX(0deg);
    -moz-transform: rotateX(0deg);
    -o-transform: rotateX(0deg);
    -ms-transform: rotateX(0deg);
    transform: rotateX(0deg);
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  99% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
    -webkit-transform: rotateX(-90deg);
    -moz-transform: rotateX(-90deg);
    -o-transform: rotateX(-90deg);
    -ms-transform: rotateX(-90deg);
    transform: rotateX(-90deg);
  }
}
@-moz-keyframes show {
  0% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }

  100% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }
}
@-webkit-keyframes show {
  0% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }

  100% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }
}
@-o-keyframes show {
  0% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }

  100% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }
}
@-ms-keyframes show {
  0% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }

  100% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }
}
@keyframes show {
  0% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }

  100% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }
}
@-moz-keyframes hide {
  0% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }
}
@-webkit-keyframes hide {
  0% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }
}
@-o-keyframes hide {
  0% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }
}
@-ms-keyframes hide {
  0% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }
}
@keyframes hide {
  0% {
    opacity: 1;
    -ms-filter: none;
    filter: none;
  }

  100% {
    opacity: 0;
    filter: alpha(opacity=0);
    -ms-filter: "progid:DXImageTransform.Microsoft.Alpha(Opacity=0)";
  }
}

)rawliteral";