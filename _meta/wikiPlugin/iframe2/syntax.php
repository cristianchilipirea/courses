<?php
/**
 * Plugin Iframe: Inserts an iframe element to include the specified url
 *
 * @license    GPL 2 (http://www.gnu.org/licenses/gpl.html)
 * @author     Christopher Smith <chris@jalakai.co.uk>
 */
 // must be run within Dokuwiki
if(!defined('DOKU_INC')) die();

if(!defined('DOKU_PLUGIN')) define('DOKU_PLUGIN',DOKU_INC.'lib/plugins/');
require_once(DOKU_PLUGIN.'syntax.php');

/**
 * All DokuWiki plugins to extend the parser/rendering mechanism
 * need to inherit from this class
 */
class syntax_plugin_iframe2 extends DokuWiki_Syntax_Plugin {

    function getType() { return 'substition'; }
    function getSort() { return 306; }
    function connectTo($mode) { $this->Lexer->addSpecialPattern('{{url2>.*?}}',$mode,'plugin_iframe2'); }

    function handle($match, $state, $pos, Doku_Handler $handler){
        $match = substr($match, 7, -2);
        list($url, $alt, $code)   = explode('|',$match,3);
        list($url, $param) = explode(' ',$url,2);

        // javascript pseudo uris allowed?
        if (!$this->getConf('js_ok') && substr($url,0,11) == 'javascript:'){
            $url = false;
        }

        // set defaults
        $opts = array(
                    'url'    => $url,
                    'width'  => '98%',
                    'height' => '400px',
                    'alt'    => $alt,
                    'scroll' => true,
                    'border' => true,
                    'align'  => false,
					'code'   => $code,
                );

        // handle size parameters
        $matches=array();
        if(preg_match('/\[?(\d+(em|%|pt|px)?)\s*([,xX]\s*(\d+(em|%|pt|px)?))?\]?/',$param,$matches)){
            if($matches[4]){
                // width and height was given
                $opts['width'] = $matches[1];
                if(!$matches[2]) $opts['width'] .= 'px'; //default to pixel when no unit was set
                $opts['height'] = $matches[4];
                if(!$matches[5]) $opts['height'] .= 'px'; //default to pixel when no unit was set
            }elseif($matches[2]){
                // only height was given
                $opts['height'] = $matches[1];
                if(!$matches[2]) $opts['height'] .= 'px'; //default to pixel when no unit was set
            }
        }

        // handle other parameters
        if(preg_match('/noscroll(bars?|ing)?/',$param)){
            $opts['scroll'] = false;
        }
        if(preg_match('/no(frame)?border/',$param)){
            $opts['border'] = false;
        }
        if(preg_match('/(left|right)/',$param,$matches)){
            $opts['align'] = $matches[1];
        }

        return $opts;
    }

    function render($mode, Doku_Renderer $R, $data) {
		global $USERINFO;
		$username = substr($USERINFO['mail'],0,-6);
        if($mode != 'xhtml') return false;

        if(!$data['url']){
            $R->doc .= '<div class="iframe">'.hsc($data['alt']).'</div>';
        }else{
			$timestamp = time();
            $opts = array(
                        'title' => $data['alt'],
                        'src'   => $data['url']."&username=".$username."&key=".md5($username."".$data['code']."".$timestamp)."&timestamp=".$timestamp,
                        'style' => 'width:'.$data['width'].'; height:'.$data['height'],
                        );
            if(!$data['border']) $opts['frameborder'] = 0;
            if(!$data['scroll']) $opts['scrolling'] = 'no';
            if($data['align'])   $opts['align'] = $data['align'];
            $params = buildAttributes($opts);
            $R->doc .= "<iframe $params>".hsc($alt).'</iframe>';
        }

        return true;
    }
}
